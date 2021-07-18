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
	for (int i = 0; i < numberOfPoints; ++i) {
		int pointRadius = RandomFloat(radius - 0.4, radius + 0.4);
		float angle = 2 * M_PI * i / numberOfPoints;
		float x = cos(angle) * pointRadius;
		float y = sin(angle) * pointRadius * -1;

		points.push_back(olc::vi2d(startX + x, startY + y));
	}
};


void Asteriod::updatePoints(float newX, float newY, float elapsedTime) {
	
	std::transform(
		points.begin(),
		points.end(),
		points.begin(),
		[this, newX, newY, elapsedTime](olc::vi2d point) {
			point.x += 100* elapsedTime + 2;
			point.y += 100* elapsedTime + 2;
			return olc::vi2d(point);
		}
	);
	currentX = newX;
	currentY = newY;
	
}