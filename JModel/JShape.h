#pragma once
#include <algorithm>
#include <cmath>
#include "JPoint.h"
#include "JConstants.h"
#include "JShader.h"


class JShape {
public:

	/*
	* SDF����
	* �ṩSDF���볡
	* @author ������
	* @version 1.2,2021-05-20
	*/
	virtual float sdFunc(const JPoint3f& p) const = 0;

	std::shared_ptr<JShader> shader;
};

/*
* <2D��״>
* <����2D��״>
* @author ������
* @version 1.2,2021-05-20
*/
class JShape2D : public JShape {
public:
	JShape2D(const JPoint2f& p) :pos(p) {}

	virtual float sdFunc(const JPoint3f& p)const override {}

	JPoint2f pos;
};

/*
* <2DԲ��>
* <����2D��״���ṩSDF���볡>
* @author Inigo,������
* @version 1.2,2021-05-20
*/
class JCircle : public JShape2D {
public:
	JCircle(const JPoint2f& pos, float radius) : JShape2D(pos), r(radius) {}

	float sdFunc(const JPoint3f& p)const override{
		JVector2f v = p.XY() - pos;
		return v.Length() - r;
	}

	friend std::ostream& operator<<(std::ostream& os, const JCircle& cle) {
		os << "[circle:: pos:" << cle.pos << ", radius:" << cle.r << "]";
		return os;
	}

private:
	float r;
};

/*
* <2DBox>
* <����2D��״���ṩSDF���볡>
* @author Inigo,������
* @version 1.2,2021-05-20
*/
class JBox2D : public JShape2D {
public:
	JBox2D(const JPoint2f& pos, const JVector2f& diagonal) :JShape2D(pos), b(diagonal) {}

	float sdFunc(const JPoint3f& p)const override {
		JVector2f v = p.XY() - pos;
		JVector2f d = Abs(v) - b;
		return d.Length() + std::min(std::max(d.X(), d.Y()), 0.0f);
	}

	friend std::ostream& operator<<(std::ostream& os, const JBox2D& cle) {
		os << "[circle:: pos:" << cle.pos << ", radius:" << cle.b << "]";
		return os;
	}

private:
	JVector2f b;
};

/*
* <Բ����״>
* <��������״ʧȥ���>
* @param [shape][Ҫ�������״]
* @param [p][��ǰ������λ��]
* @param [r][Բ���̶�]
*/
static float opRound2D(const JShape2D& shape, const JPoint3f& p, float r){
	return shape.sdFunc(p) - r;
}

/*
* <����>
* <��������״ӵ���ڻ�>
* @param [shape][Ҫ�������״]
* @param [p][��ǰ������λ��]
* @param [r][�����̶�]
*/
static float opOnion(const JShape2D& shape, const JPoint3f& p, float r){
	return std::abs(shape.sdFunc(p)) - r;
}


//----------------------------------------������3D������--------------------------------------------

/*
* <3D��״>
* <����3D��״>
* @author ������
* @version 1.2,2021-05-20
*/
class JShape3D : public JShape {
public:
	JShape3D(const JPoint3f& p) :pos(p) {}

	virtual float sdFunc(const JPoint3f& p)const override { return 0.0f; }

	void setShader(std::shared_ptr<JShader> sh) {
		shader = sh;
	}

	JPoint3f pos;
};

class JSphere : public JShape3D {
public:
	JSphere(const JPoint3f& pos, float radius) :JShape3D(pos), radius(radius) {}

	float sdFunc(const JPoint3f& p)const override {
		JVector3f v = p - pos;
		return Length(v) - radius;
	}

	friend std::ostream& operator<<(std::ostream& os, const JSphere& js) {
		os << "[Sphere:: pos:" << js.pos << ",radius:" << js.radius << "]";
		return os;
	}

private:
	float radius;
};

class JBox3D :public JShape3D {
public:
	JBox3D(const JPoint3f& p, const JVector3f& d) :JShape3D(p), diagonal(d) {}

	float sdFunc(const JPoint3f& p)const override {
		JVector3f v = p - pos;
		JVector3f q = Abs(v) - diagonal;
		return Length(Max(q, 0.0)) + std::min(std::max(q.X(), std::max(q.Y(), q.Z())), 0.0f);
	}

	friend std::ostream& operator<<(std::ostream& os, const JBox3D& jb) {
		os << "[Box3D:: pos:" << jb.pos << ",diagonal:" << jb.diagonal << "]";
		return os;
	}

private:
	JVector3f diagonal;

};

//3d����

/*
* <����>
* <��һ��3D��Ԫһ��Ϊ2������ࣩ���������ƿ���Ȼ����������>
* @param [shape][Ҫ�������״]
* @param [p][��ǰ������λ��]
* @param [h][����̶�]
*/
//static float opElongate(const JShape3D& shape, const JPoint3f& p, const JPoint3f& h)
//{
//	JVector3f q = Abs(p) - h;
//	JVector3f qa = Max(q, 0.0f);
//	return shape.sdFunc(V2P(qa)) + std::min(std::max(q.X(), std::max(q.Y(), q.Z())), 0.0f);
//}

/*
* <Բ����״>
* <��������״ʧȥ���>
* @param [shape][Ҫ�������״]
* @param [p][��ǰ������λ��]
* @param [r][Բ���̶�]
*/
//static float opRound3D(const JShape3D& shape, const JPoint3f& p, float r) {
//	return shape.sdFunc(p) - r;
//}
//
///*
//* <����ڲ������״���Ӻ��>
//* <����ͬ��Բ��>
//* @param [shape][Ҫ�������״]
//* @param [p][��ǰ������λ��]
//* @param [thickness][�̶�]
//*/
//static float opOnion(const JShape3D& shape, const JPoint3f& p, float thickness) {
//	return std::abs(shape.sdFunc(p)) - thickness;
//}

/*
* <ƽ�ƻ���ת>
* <ƽ�ƻ���ת��״>
* @param [d1][��һ����״��SDF]
* @param [d2][�ڶ�����״��SDF]
* @param [k][ƽ���̶�]
*/
//static float opTx(const JShape3D& shape, const JPoint3f& p, )


//2dת3d

/*
* <����>
* <����2dʹ֮��Ϊ3D>
* @param [shape][Ҫ�������״]
* @param [p][��ǰ������λ��]
* @param [h][����̶�]
*/
static float opExtrusion(const JShape2D& shape, const JPoint3f& p, float h) {
	float d = shape.sdFunc(p);
	JVector2f w(d, std::abs(p.Z()) - h);
	return std::min(std::max(w.X(), w.Y()), 0.0f) + Length(Max(w, 0.0f));
}

/*
* <��ת>
* <��Y����ת2dʹ֮��Ϊ3D>
* @param [shape][Ҫ�������״]
* @param [p][��ǰ������λ��]
* @param [o][��ת�̶�]
*/
static float opRevolutionY(const JShape2D& shape, const JPoint3f& p, float o) {
	JVector3f q(Length(P2V(p.XZ())) - o, p.Y(), 0.0f);
	return shape.sdFunc(q);
}

