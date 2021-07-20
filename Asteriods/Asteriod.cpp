#include "Asteriod.h"
#include "Util.h"
#include <cstdlib>
#include <ctime>


Asteriod::Asteriod(
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
	
	vx = RandomFloat(-30.0, 30.0);
	vy = RandomFloat(-30.0, 30.0);

	printf("Vx: %f, Vy: %f\n", vx, vy);

	for (int i = 0; i < numberOfPoints; ++i) {
		int pointRadius = RandomFloat(radius - 0.4, radius + 0.4);
		float angle = 2 * M_PI * i / numberOfPoints;
		float x = -currentX + cos(angle) * pointRadius;
		float y = -currentY + sin(angle) * pointRadius * -1;

		points.push_back(std::pair<float,float>(x, y));
	}
};


void Asteriod::updatePoints(float newX, float newY, float elapsedTime) {
	

	currentX += vx * elapsedTime;
	currentY += vy * elapsedTime;
	
}