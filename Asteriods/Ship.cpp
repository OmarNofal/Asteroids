#include "Ship.h"
#include "Globals.h"
#define _USE_MATH_DEFINES
#include <cmath>



Ship::Ship(): posx(0), posy(0) {
};


void Ship::move(float elapsedTime) {
	posx += vx * elapsedTime;
	posy += vy  * elapsedTime;
}

void Ship::accelerate(float elapsedTime) {
	vx += 240.0f * sin(rotation) * elapsedTime;
	vy += 240.0f * cos(rotation) * elapsedTime;
}

void Ship::decelerate(float elapsedTime) { // Drag. f el fada2 ezay? m3rf4.¯\_(^^)_/¯
	if (abs(getVelocityMagnitude()) < 0.01) return;
	vx += -0.7 * vx * elapsedTime;
	vy += -0.7 * vy * elapsedTime;
}

float Ship::getVelocityMagnitude() const {
	return sqrt(vx * vx + vy * vy);
};

olc::vi2d Ship::getHead() const {
	return Point(
		posx + height * sin(rotation), 
		posy + height * cos(rotation)
	);
};

olc::vi2d Ship::getLeft() const {
	return Point(
		posx + width * sin(rotation - 120 * M_PI / 180),
		posy + width * cos(rotation - 120 * M_PI / 180)
	);
};

olc::vi2d Ship::getRight() const {
	return Point(
		posx + width * sin(rotation + 120 * M_PI / 180),
		posy + width * cos(rotation + 120 * M_PI / 180)
	);
};