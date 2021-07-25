#pragma once
#include "Globals.h"
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

	/*
	 Returns angle between 2 vectors in radians.
	*/
	static double Angle2V(const Point& v1, const Point& v2) {
		double dot_product = (double)v1.x * v2.x + (double) v1.y * v2.y;
		double divisor = ((double)v1.mag()) * v2.mag();
		double cosineTheta = dot_product / divisor;
		if (cosineTheta < -1)
			cosineTheta = -1.0f;
		else if (cosineTheta > 1)
			cosineTheta = 1.0f;
		return acos(cosineTheta); // radians
	}

};
