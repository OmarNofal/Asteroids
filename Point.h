#pragma once

#include <iostream>
#include <cmath>
#include "olcPixelGameEngine.h"
 
struct Point {
	int32_t x, y;
	
	Point(int32_t x = 0, int32_t y = 0) {
		this->x = x;
		this->y = y;
	}

	olc::vi2d toGamePoint() {
		return olc::vi2d(x, y);
	}

	int distance(const Point& p) const  {
		return (int) sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
	}
	
	friend std::ostream& operator<<(std::ostream& stream, const Point& p);
};


std::ostream& operator<<(std::ostream& stream, const Point& p) {
	stream << "(" << p.x << ", " << p.y << ")";
	return stream;
}