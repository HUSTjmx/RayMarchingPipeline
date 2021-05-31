#pragma once
#include "JModel.h"
#include "JLight.h"
#include "JMaterial.h"
#include "JConstants.h"
//todo
class JScene {
public:
	JScene() :render_id(-1) {}

	void addActor(std::shared_ptr<JModel> ac) {
		actors.push_back(ac);
	}

	void addLight(std::shared_ptr<JLight> jl) {
		lights.push_back(jl);
	}

	float map(JPoint3f p){
		float sdf = J_MaxFloat;
		render_id = 0;

		if (actors.empty())return sdf;
		for (int i = 0;i < actors.size();i++){
			float d2 = (*(actors[i].get())).SDF(p);
			//std::cout << d2 << std::endl;
			if (sdf > d2){
				sdf = d2;
				render_id = i;
			}
		}
		return sdf;
	}

	float fastMap(JPoint3f p) {
		return actors[render_id].get()->SDF(p);
	}

	int getRenderID() {
		return render_id;
	}

	std::shared_ptr<JMaterial> getRenderMaterial()
	{
		auto a = actors[render_id].get();
		return a->getRenderMat();
	}

	std::shared_ptr<JShader> getRenderShader() {
		auto a = actors[render_id].get();
		return a->getRenderShader();
	}

	JSky getSky() {
		return sky;
	}

	std::vector<std::shared_ptr<JLight>> lights;
private:
	std::vector<std::shared_ptr<JModel>> actors;
	JSky sky;
	int render_id;
};