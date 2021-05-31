#pragma once
#include "JVector.h"

class JMaterial {
public:
	JMaterial(JVector3f col, float a) :color(col), alpha(a) {}

	JVector3f color;
	float alpha;
};

class JMaterialPBR :public JMaterial {

public:
	JMaterialPBR(JVector3f col, float a, float metallic, float smoothness, float refl) :
		JMaterial(col, a), metallic(metallic), smoothness(smoothness), reflectance(refl) {}

	float metallic;
	float smoothness;
	float reflectance;
};

class JMaterialCoat : public JMaterialPBR {
public:
	JMaterialCoat(JVector3f col, float a, float metallic, float smoothness, float refl, float cc, float ccr) :
		JMaterialPBR(col, a, metallic, smoothness, refl), clearCoat(cc), clearCoatRoughness(ccr) {}
	float clearCoat;
	float clearCoatRoughness;
};
