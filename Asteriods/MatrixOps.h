#include <vector>
#include <cmath>

class MatrixOps {

public:

	static void rotateAroundCenter(std::vector<Point> &points, float angle) {
		Point mid(getMidPoint(points));
		for (size_t i = 0; i < points.size(); i++) {
			Point& p = points[i];
			p.x -= mid.x;
			p.y -= mid.y;

			int32_t new_x = mid.x + p.x * cos(angle) - p.y * sin(angle);
			int32_t new_y = mid.y + p.x * sin(angle) + p.y * cos(angle);
			
			p.x = new_x;
			p.y = new_y;
		}
	}

	static Point getMidPoint(const std::vector<Point>& vec) {
		int x = 0;
		int y = 0;
		for (auto& point : vec) {
			x += point.x;
			y += point.y;
		}
		return Point(x / vec.size(), y / vec.size());
	}
};