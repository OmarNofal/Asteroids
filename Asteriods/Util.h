#include <stdlib.h>

float RandomFloat(float a = 0.0f, float b = 1.0f) {
	float random = ((float)rand()) / RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return r + a;
}