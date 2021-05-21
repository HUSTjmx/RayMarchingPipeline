#pragma once
#include <limits>
static constexpr float Infinity = std::numeric_limits<float>::infinity();
static constexpr float MaxFloat = std::numeric_limits<float>::max();

static float Jmix(float a, float b, float t) {
	return a * (1 - t) + t * b;
}