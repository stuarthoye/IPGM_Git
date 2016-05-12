#pragma once

class Point 
{
public:
	Point();
	Point(const Point &point);
	Point(int x, int y, int index);
	~Point();
	int x, y, vector_offset, index;
};
