#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
	index = 0;
}

Point::Point(const Point &point) {
	x = point.x;
	y = point.y;
	index = point.index;
}

Point::Point(int x1, int y1, int index1) {
	x = x1;
	y = y1;
	index = index1;
}

Point::~Point() {

}