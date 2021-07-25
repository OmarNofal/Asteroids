#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "olcPixelGameEngine.h"



enum class Rotation {
	C, AC // clockwise & anti-clockwise
};

class Ship {	

public:
	
	const float rotationSpeed = .03;
	
	const int height = 10;
	const int width = 5;

	float posx = 0;
	float posy = 0;
	
	Ship();

	float rotation = 0.0f;

	float vx = 0.0f;
	float vy = 0.0f;

	void move(float elapsedTime);
	void accelerate(float elapsedTime);
	void decelerate(float elapsedTime);

	float getVelocityMagnitude() const;

	olc::vi2d getHead() const;
	olc::vi2d getLeft() const;
	olc::vi2d getRight() const;
};
