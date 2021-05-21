#pragma once
#include "JShape.h"
#include "JTransform.h"
#include "JVector.h"
#include <memory>

using namespace std;

class ShapeDecorator {
public:
	virtual JPoint3f SolvePos(const JPoint3f& p) = 0;
	virtual float Process(float sdf) const = 0;
};

class opElongate :public ShapeDecorator {
public:
	opElongate(const JPoint3f& hh) :h(hh), q(const_v3f) {}

	JPoint3f SolvePos(const JPoint3f& p)override {
		q = (Abs(p) - h);
		JVector3f qa = Max(q, 0.0f);
		return V2P(qa);
	}

	float Process(float sdf)const {
		return sdf + std::min(std::max(q.X(), std::max(q.Y(), q.Z())), 0.0f);
	}
private:
	JPoint3f h;
	JVector3f q;
};

class opTx : public ShapeDecorator {
public:
	opTx(const JTransform& jt) : trans(jt) {}

	JPoint3f SolvePos(const JPoint3f& p)override {
		JPoint3f t = trans.MulP(p);
		return t;
	}

	float Process(float sdf)const override {
		return sdf;
	}

private:
	JTransform trans;
};

class opScale :public ShapeDecorator {
public:
	opScale(float ss) :s(ss) {}

	JPoint3f SolvePos(const JPoint3f& p)override {
		return p / s;
	}

	float Process(float sdf)const override {
		return sdf * s;
	}

private:
	float s;
};

class opRound3D : public ShapeDecorator {
public:
	opRound3D(float rr) : r(rr) {};

	JPoint3f SolvePos(const JPoint3f& p)override {
		return JPoint3f(p);
	}

	float Process(float sdf)const override {
		return sdf - r;
	}

private:
	float r;
};

class opOnion : public ShapeDecorator {
public:
	opOnion(float rr) : thickness(rr) {};

	JPoint3f SolvePos(const JPoint3f& p)override {
		return JPoint3f(p);
	}

	float Process(float sdf)const override {
		return std::abs(sdf) - thickness;
	}

private:
	float thickness;
};

class JShapeProcessLine {
public:
	void add(std::shared_ptr<ShapeDecorator> sd) {
		decorators.push_back(sd);
	}

	float Do(const JPoint3f& p, const JShape& shape) {
		JPoint3f temp_p = p;

		for (auto it = decorators.begin();it != decorators.end();it++)
			temp_p = (*it).get()->SolvePos(temp_p);

		float sdf = shape.sdFunc(temp_p);

		for (auto it = decorators.rbegin();it != decorators.rend();it++)
			sdf = (*it).get()->Process(sdf);

		return sdf;
	}

private:
	std::vector<std::shared_ptr<ShapeDecorator>> decorators;
};