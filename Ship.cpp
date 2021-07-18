#include "Ship.h"

#define _USE_MATH_DEFINES
#include <cmath>



Ship::Ship(): posx(0), posy(0) {
};


void Ship::move(float elapsedTime) {
	posx += vx * elapsedTime;
	posy += vy  * elapsedTime;
}

void Ship::accelerate(float elapsedTime) {
	vx += 20.0f * sin(rotation) * elapsedTime;
	vy += 20.0f * cos(rotation) * elapsedTime;

	/*if (vx > 70.0f) { vx = 70.0f; }
	else if (vx < -70.0f) { vx = -70.f; }
	if (vy > 70.0f) { vy = 70.0f; }
	else if (vy < -70.0f) { vy = -70.f; }*/ // Limiting speed code

}

float Ship::getVelocityMagnitude() const {
	return sqrt(vx * vx + vy * vy);
};

olc::vi2d Ship::getHead() const {
	return olc::vi2d(
		posx + height * sin(rotation), 
		posy + height * cos(rotation)
	);
};

olc::vi2d Ship::getLeft() const {
	return olc::vi2d(
		posx + width * sin(rotation - 120 * M_PI / 180),
		posy + width * cos(rotation - 120 * M_PI / 180)
	);
};

olc::vi2d Ship::getRight() const {
	return olc::vi2d(
		posx + width * sin(rotation + 120 * M_PI / 180),
		posy + width * cos(rotation + 120 * M_PI / 180)
	);
};