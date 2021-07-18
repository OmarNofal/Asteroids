#include <stdlib.h>

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return r + a;
}