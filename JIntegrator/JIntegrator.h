#pragma once
#include <memory>
#include "JSample.h"
#include "JCamera.h"
#include "JSetup.h"
#include "JScene.h"
#include "JMaterial.h"

class JIntegrator {
public:
	JIntegrator(const JSample& sp, const JCamera& cam) {
		sample = std::make_shared<JSample>(sp);
		camera = std::make_shared<JCamera>(cam);
	}

	virtual JVector3f Render(const JPoint2f& p, JScene& scene){
		auto sp = sample.get();
		JRay ray = camera.get()->getRay(p, *sp);
		float t = trace(ray, scene);
		if (t > ray.T_MAX())return scene.getSky().getCol(ray.D());
		return Li(ray, t, scene);
	}

	JVector3f Li(const JRay& ray, float t, JScene& scene) {
		JPoint3f pos = ray(t);
		JVector3f N = Normalize(calNormal(JVector3f(pos.X(), pos.Y(), pos.Z()), scene));
		//N = Permute(N, 0, 2, 1);
		auto m1 = scene.getRenderMaterial();
		auto sh1 = scene.getRenderShader();

		JVector3f V = -ray.D();
		JVector3f Lo(0.0, 0.0, 0.0);

		for (int i = 0;i < scene.lights.size();i++) {
			JVector3f L =  -scene.lights[i].get()->getDir(pos);
			JVector3f Li = scene.lights[i].get()->getCol(pos);
			JVector3f ambient = JVector3f(0.01, 0.01, 0.01) * Li;
			JVector3f diffuse = Li * sh1.get()->getDiffuse(N, L) * 0.8;
			JVector3f spec = Li * sh1.get()->getSpecular(N, L, V, 0.1) * 1.4;
			//std::cout << diffuse << spec << diffuse + spec << std::endl;
			Lo = Lo + (ambient + diffuse + spec) * m1.get()->color;

			Lo = Lo / (Lo + JVector3f(1.0));
			Lo = Pow(Lo, 1.0f / J_Gamma);
			
		}
		
		return Lo;
	}

private:
	float trace(const JRay& ray, JScene& scene) const{
		int step = JSetup::instance().MAX_STEP;
		float t = 0.0f;

		for (int i = 0;i < step;i++) {
			JPoint3f p = ray(t);
			//std::cout << ray.D() << std::endl;
			float sdf = scene.map(p);
			//std::cout << sdf << std::endl;
			if (sdf < 0.0001 || t > ray.T_MAX())break;
			t = t + sdf * 0.3;
		}
		return t;
	}
	JVector3f calNormal(const JVector3f& pos, JScene& scene) const{
		JVector3f nor = JVector3f(
			scene.fastMap(pos + JVector3f(0.0001, 0.0, 0.0)) - scene.fastMap(pos - JVector3f(0.0001, 0.0, 0.0)),
			scene.fastMap(pos + JVector3f(0.0, 0.0001, 0.0)) - scene.fastMap(pos - JVector3f(0.0, 0.0001, 0.0)),
			scene.fastMap(pos + JVector3f(0.0, 0.0, 0.0001)) - scene.fastMap(pos - JVector3f(0.0, 0.0,0.0001))
		);
		//std::cout << nor << std::endl;
		return nor;
	}

	std::shared_ptr<JSample> sample;
	std::shared_ptr<JCamera> camera;
};