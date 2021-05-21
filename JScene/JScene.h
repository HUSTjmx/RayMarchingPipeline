#pragma once
#include "JModel.h"

//todo
class JScene {
public:
	void addActors(std::shared_ptr<JModel> ac) {
		actors.push_back(ac);
	}

	float map(JPoint3f p){
		float sdf = MaxFloat;
		render_id = 0;

		if (actors.empty())return sdf;
		for (int i = 0;i < actors.size();i++){
			float d2 = *(actors[i].get()).SDF();
			if (sdf > d2){
				sdf = d2;
				render_id = i;
			}
		}
		return sdf;
	}

	int getRenderID() {
		return render_id;
	}

	JMaterial getRenderMaterial()
	{
		return *(actors[render_id].get()).getRenderMat();
	}

private:
	std::vector<std::shared_ptr<JModel>> actors;
	int render_id;
};