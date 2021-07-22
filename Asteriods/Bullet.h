#ifndef BULLET_H
#define BULLET_H

class Bullet {

public:
	Bullet(float x = 0.0f,
		float y = 0.0f,
		float vx = 70,
		float vy = 70,
		float radius = 1);

	void move(float);

	float posx;
	float posy;

	float vx;
	float vy;

	int radius;
};


#endif // !BULLET_H

