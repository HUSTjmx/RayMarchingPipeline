#pragma once
#include <algorithm>
#include <cmath>
#include "JPoint.h"
#include "JConstants.h"
#include "JShader.h"


class JShape {
public:

	/*
	* SDF函数
	* 提供SDF距离场
	* @author 蒋孟贤
	* @version 1.2,2021-05-20
	*/
	virtual float sdFunc(const JPoint3f& p) const = 0;

	std::shared_ptr<JShader> shader;
};

/*
* <2D形状>
* <基本2D形状>
* @author 蒋孟贤
* @version 1.2,2021-05-20
*/
class JShape2D : public JShape {
public:
	JShape2D(const JPoint2f& p) :pos(p) {}

	virtual float sdFunc(const JPoint3f& p)const override {}

	JPoint2f pos;
};

/*
* <2D圆类>
* <基本2D形状，提供SDF距离场>
* @author Inigo,蒋孟贤
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
* <基本2D形状，提供SDF距离场>
* @author Inigo,蒋孟贤
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
* <圆滑形状>
* <让整个形状失去棱角>
* @param [shape][要处理的形状]
* @param [p][当前步进的位置]
* @param [r][圆滑程度]
*/
static float opRound2D(const JShape2D& shape, const JPoint3f& p, float r){
	return shape.sdFunc(p) - r;
}

/*
* <环化>
* <让整个形状拥有内环>
* @param [shape][要处理的形状]
* @param [p][当前步进的位置]
* @param [r][环化程度]
*/
static float opOnion(const JShape2D& shape, const JPoint3f& p, float r){
	return std::abs(shape.sdFunc(p)) - r;
}


//----------------------------------------以下是3D的世界--------------------------------------------

/*
* <3D形状>
* <基本3D形状>
* @author 蒋孟贤
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

//3d操作

/*
* <拉长>
* <将一个3D基元一分为2（或更多），将他们移开，然后连接起来>
* @param [shape][要处理的形状]
* @param [p][当前步进的位置]
* @param [h][拉伸程度]
*/
//static float opElongate(const JShape3D& shape, const JPoint3f& p, const JPoint3f& h)
//{
//	JVector3f q = Abs(p) - h;
//	JVector3f qa = Max(q, 0.0f);
//	return shape.sdFunc(V2P(qa)) + std::min(std::max(q.X(), std::max(q.Y(), q.Z())), 0.0f);
//}

/*
* <圆滑形状>
* <让整个形状失去棱角>
* @param [shape][要处理的形状]
* @param [p][当前步进的位置]
* @param [r][圆滑程度]
*/
//static float opRound3D(const JShape3D& shape, const JPoint3f& p, float r) {
//	return shape.sdFunc(p) - r;
//}
//
///*
//* <雕刻内部或给形状增加厚度>
//* <增加同心圆层>
//* @param [shape][要处理的形状]
//* @param [p][当前步进的位置]
//* @param [thickness][程度]
//*/
//static float opOnion(const JShape3D& shape, const JPoint3f& p, float thickness) {
//	return std::abs(shape.sdFunc(p)) - thickness;
//}

/*
* <平移或旋转>
* <平移或旋转形状>
* @param [d1][第一个形状的SDF]
* @param [d2][第二个形状的SDF]
* @param [k][平滑程度]
*/
//static float opTx(const JShape3D& shape, const JPoint3f& p, )


//2d转3d

/*
* <拉伸>
* <拉伸2d使之成为3D>
* @param [shape][要处理的形状]
* @param [p][当前步进的位置]
* @param [h][拉伸程度]
*/
static float opExtrusion(const JShape2D& shape, const JPoint3f& p, float h) {
	float d = shape.sdFunc(p);
	JVector2f w(d, std::abs(p.Z()) - h);
	return std::min(std::max(w.X(), w.Y()), 0.0f) + Length(Max(w, 0.0f));
}

/*
* <旋转>
* <绕Y轴旋转2d使之成为3D>
* @param [shape][要处理的形状]
* @param [p][当前步进的位置]
* @param [o][旋转程度]
*/
static float opRevolutionY(const JShape2D& shape, const JPoint3f& p, float o) {
	JVector3f q(Length(P2V(p.XZ())) - o, p.Y(), 0.0f);
	return shape.sdFunc(q);
}

