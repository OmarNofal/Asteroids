#include "Bullet.h"


Bullet::Bullet(
	float x,
	float y,
	float vx,
	float vy,
	float radius
) : posx(x), posy(y), vx(vx), vy(vy), radius(radius) {};

void Bullet::move(float elapsedTime) {
	posx += vx * elapsedTime;
	posy += vy * elapsedTime;
}