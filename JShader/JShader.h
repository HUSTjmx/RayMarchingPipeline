#pragma once
#include<algorithm>
#include <iostream>
#include"JConstants.h"
class JShader {
public:
	virtual float getDiffuse(const JVector3f& N, const JVector3f& L) { return 0.0; }
	virtual float getSpecular(const JVector3f& N, const JVector3f& L, const JVector3f& V, float roughness) { return 0.0; }
};

class JPhongShader : public JShader{
public:
	virtual float getDiffuse(const JVector3f& N, const JVector3f& L) override{
		//std::cout << Dot(N, L) << std::endl;
		return JClamp(Dot(N, L), 0.0, 10.0);
	}

	virtual float getSpecular(const JVector3f& N, const JVector3f& L, const JVector3f& V, float roughness) override{
		JVector3f R = -L + N * 2.0 * Dot(L, N);
		R = Normalize(R);
		float temp = Dot(R, V);
		temp = JClamp(temp, 0.0, 10.0);
		temp = pow(temp, 1 / roughness);
		return temp;
	}
};

static std::shared_ptr<JPhongShader> phongShader = std::make_shared<JPhongShader>();