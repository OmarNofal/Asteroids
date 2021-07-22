#pragma once
#include <stdlib.h>
#define __USE_MATH_DEFINES
#include <cmath>


namespace util {

	static long long s = 0;

	static float RandomFloat(float a = 0.0f, float b = 1.0f) {
		float random = ((float)rand()) / RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return r + a;
	};

	static bool IsPointInsideCircle(
		float px, // point x
		float py,	// point y
		float rx, // center x
		float ry, // center y
		float radius
	) {
		return pow(px - rx, 2) + pow(py - ry, 2) < pow(radius, 2);
	};
};
