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
	JMaterialPBR(JVector3f col, float a, float metallic, float smoothness) :JMaterial(col, a), metallic(metallic), smoothness(smoothness) {}

	float metallic;
	float smoothness;
};