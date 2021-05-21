#pragma once
#include "JTransform.h"

class JCamera {
public:
	JCamera(const JVector3f& o, const JVector3f& d, float cr) :ro(o), rd(d), cr(cr) {
		JVector3f cw = Normalize(ta - ro);
		JVector3f cp = JVector3f(sin(cr), cos(cr), 0.0f);
		JVector3f cu = Normalize(Cross(cw, cp));
		JVector3f cv = Normalize(Cross(cu, cw));

		mat << cu.X(), cu.Y(), cu.Z(), cv.X(), cv.Y(), cv.Z(), cw.X, cw.Y(), cw.Z();
	}

	JVector3f mul(const JVector3f& v)
	{
		Vector3f v2(v.X(), v.Y(), v.Z());
		v2 = mat * v2;
		return JVector3f(v2[0], v2[1], v2[2]);
	}



private:
	JVector3f ro;
	JVector3f rd;
	float cr;

	Matrix3f mat;
};