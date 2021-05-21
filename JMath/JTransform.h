#pragma once
#include "Eigen/Dense"
#include "JPoint.h"
using namespace Eigen;

class JTransform {
public:
	JTransform(Matrix4f m) :mat(m),mat_inv(m.inverse()) {}

	JVector3f MulV(const JVector3f& v)const {
		Vector4f temp(v.X(), v.Y(), v.Z(), 0.0f);
		temp = mat_inv * temp;
		return JVector3f(temp[0], temp[1], temp[2]);
	}

	JPoint3f MulP(const JPoint3f& p) const
	{
		Vector4f temp(p.X(), p.Y(), p.Z(), 1.0f);
		temp = mat_inv * temp;
		return JPoint3f(temp[0] / temp[3], temp[1] / temp[3], temp[2] / temp[3]);
	}

private:
	Matrix4f mat;
	Matrix4f mat_inv;
};