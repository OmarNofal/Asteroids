#ifndef BULLET_H
#define BULLET_H

#include "Asteriod.h"

class Bullet {

public:
	Bullet(
		float x = 0.0f,
		float y = 0.0f,
		float vx = 150,
		float vy = 150,
		float radius = 1,
		Asteroid* target = nullptr
	);

	void move(float);

	float posx;
	float posy;

	float vx;
	float vy;

	int radius;
	Asteroid* target;
};


#endif // !BULLET_H

