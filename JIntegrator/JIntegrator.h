#pragma once
#include <memory>
#include "JSample.h"
#include "JCamera.h"

class JIntegrator {
public:
	JIntegrator(const JSample& sp, const JCamera& cam) {
		sample = std::make_shared<JSample>(sp);
		camera = std::make_shared<JCamera>(cam);
	}

	virtual JVector3f Render(const JPoint2f& p) {
		auto sp = sample.get();
		JRay ray = camera.get()->getRay(p, *sp);
		return ray.D();
	}

	virtual JVector3f Li() {
		return JVector3f(1.0f, 0.0f, 0.0f);
	}

private:
	std::shared_ptr<JSample> sample;
	std::shared_ptr<JCamera> camera;
};