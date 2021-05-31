#pragma once
#include <limits>
static constexpr float J_Infinity = std::numeric_limits<float>::infinity();
static constexpr float J_MaxFloat = std::numeric_limits<float>::max();
static constexpr float J_Gamma = 2.2f;

static float Jmix(float a, float b, float t) {
	return a * (1 - t) + t * b;
}

static float JClamp(float a, float min_, float max_) {
	if (a < min_)return min_;
	if (a > max_)return max_;
	return a;
}