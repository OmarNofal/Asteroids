#define _USE_MATH_DEFINES
#include <cmath>

#include <vector>
#include <iostream>
#include "olcPixelGameEngine.h"
#include "Util.h"

#ifndef ASTERIOD_H
#define ASTERIOD_H

class Asteroid {

public:
	
	std::vector<std::pair<float, float>> points; // Points stored relative to the center

	int numberOfPoints;

	float radius;

	float startX;
	float startY;

	float currentX;
	float currentY;

	float vx;
	float vy;

	Asteroid(
		int numberOfPoints = 20, 
		float radius = 10.0f,
		float startX = 0.0f,
		float startY = 0.0f
	);

	void updatePoints(float newX, float newY, float elapsedTime);

};



#endif // !ASTERIOD_H

