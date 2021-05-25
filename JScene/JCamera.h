#pragma once
#include "JTransform.h"
#include "JSample.h"
#include "JRay.h"
#include "JSetup.h"

class JCamera {
public:
	JCamera(const JVector3f& o, const JVector3f& d, float cr, float fl = 1.0f) :ro(o), forward(d), cr(cr), fl(fl) {
		UpdateMat();
	}

	JCamera(const JCamera& camera) {
		ro = camera.pos();
		forward = camera.Forward();
		cr = camera.CR();
		fl = camera.FL();
		mat = camera.Mat();
	}

	JCamera& operator=(const JCamera& camera) {
		ro = camera.pos();
		forward = camera.Forward();
		cr = camera.CR();
		fl = camera.FL();
		return *this;
	}

	JRay getRay(const JPoint2f& p, JSample& sample) {
		JSetup setup = JSetup::instance();
		JVector2f bias = sample.getSampleAuto();
		JPoint2f sample_point = (p + bias) * setup.PIXEL_SIZE;
		JVector3f rd = mul(JVector3f(sample_point[0], sample_point[1], fl));
		return JRay(ro, rd);

	}

	void updateOrigin(JVector3f ro_) {
		ro = ro_;
		UpdateMat();
	}

	void updateForward(JVector3f forward_) {
		forward = forward_;
		UpdateMat();
	}

	JVector3f pos()const {
		return ro;
	}

	JVector3f Forward()const {
		return forward;
	}

	float CR()const {
		return cr;
	}

	float FL()const {
		return fl;
	}


	Matrix3f Mat()const {
		return mat;
	}

private:

	void UpdateMat(){
		JVector3f cw = Normalize(forward - ro);
		JVector3f cp = JVector3f(sin(cr), cos(cr), 0.0f);
		JVector3f cu = Normalize(JMX::Cross(cw, cp));
		JVector3f cv = Normalize(JMX::Cross(cu, cw));

		mat << cu.X(), cu.Y(), cu.Z(), cv.X(), cv.Y(), cv.Z(), cw.X(), cw.Y(), cw.Z();
	}

	JVector3f mul(const JVector3f& v)
	{
		Vector3f v2(v.X(), v.Y(), v.Z());
		v2 = mat * v2;
		return JVector3f(v2[0], v2[1], v2[2]);
	}

	JVector3f ro;
	JVector3f forward;
	float cr;
	float fl;

	Matrix3f mat;
};
