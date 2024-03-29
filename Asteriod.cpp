#include "Asteriod.h"
#include <cstdlib>
#include <ctime>


Asteroid::Asteroid(
	int numberOfPoints,
	float radius,
	float startX,
	float startY
) : numberOfPoints(numberOfPoints),
radius(radius),
startX(startX),
startY(startY),
currentX(startX),
currentY(startY)

{
	
	vx = util::RandomFloat(-100.0, 100.0);
	vy = util::RandomFloat(-100.0, 100.0);

	for (int i = 0; i < numberOfPoints; ++i) {
		int pointRadius = util::RandomFloat(radius - 2, radius + 2);
		float angle = 2 * M_PI * i / numberOfPoints;
		float x =  cos(angle) * pointRadius;
		float y =  sin(angle) * pointRadius * -1;

		points.push_back(std::pair<float,float>(x, y));
	}
};


void Asteroid::updatePoints(float newX, float newY, float elapsedTime) {
	

	currentX += vx * elapsedTime;
	currentY += vy * elapsedTime;
	
}