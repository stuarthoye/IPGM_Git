#pragma once
#include "PixelVector.h"
#include "Point.h"
#include <allegro5\allegro.h>

class Mapper 
{
public:
	Mapper(int height, int width);
	Mapper(int IPGM_H, int IPGM_W, int Screen_H, int Screen_W);
	~Mapper();
	void updateMap();
	Point getPoint(int index);
	bool step();
	bool complete();
	int getPointCount();
	int getFill(int i);
	int getFill(int vo, int bo);
	int getFill(Point p);
	int get();

private:
	enum DIRECTIONS {Left, Right, Up, Down};
	PixelVector * pixel_vector;
	Point * points;
	int height, width, count, direction, screen_h, screen_w;
};