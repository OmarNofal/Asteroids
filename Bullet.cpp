#include "Bullet.h"
#include "Asteriod.h"
#include "Globals.h"

Bullet::Bullet(
	float x,
	float y,
	float vx,
	float vy,
	float radius,
	Asteroid* target) : posx(x), posy(y), vx(vx), vy(vy), radius(radius), target(target) {};

void Bullet::move(float elapsedTime) {
	posx += vx * elapsedTime;
	posy += vy * elapsedTime;

	if (target == nullptr) return;

	float ax = target->currentX;
	float ay = target->currentY;

	Point v = Point(ax, ay) - Point(posx, posy);

	int32_t mag = v.mag();
	float dx = (float)v.x / mag;
	float dy = (float)v.y / mag;

	float vfx = 300 * dx;
	float vfy = 300 * dy;

	if (vfx > vx)
		vx += 200.0f * elapsedTime;
	else if (vfx < vx)
		vx -= 200.0f * elapsedTime;

	if (vfy > vy)
		vy += 200.0f * elapsedTime;
	else if (vfy < vy)
		vy -= 200.0f * elapsedTime;

	// check if bullet out of range
	if ((posx > target->currentX && vx > 0) || (posx < target->currentX && vx < 0))
		target = nullptr;
	else if ((posy > target->currentY && vy > 0) || (posy < target->currentY && vy < 0))
		target = nullptr;


}