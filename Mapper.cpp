#include "Mapper.h"
#include <iostream>
#include <climits>

Mapper::Mapper(int h, int w) {
	height = h;
	width = w;
	count = h * w;
	pixel_vector = new PixelVector(h, w);
	points = new Point[height * width];
	direction = Left;
	for (int i = 0; i < count; i++) {
		points[i] = Point();
	}
	updateMap();
}

Mapper::Mapper(int h, int w, int sh, int sw) {
	height = h;
	width = w;
	screen_h = sh;
	screen_w = sw;
	count = h * w;
	pixel_vector = new PixelVector(h, w);
	points = new Point[height * width];
	direction = Left;
	for (int i = 0; i < count; i++) {
		points[i] = Point();
	}
	updateMap();
}

Mapper::~Mapper() {
	delete[] points;
	delete pixel_vector;
}

void Mapper::updateMap() {
	int limit = 1;
	int i = 0;
	int screen_mid_x = screen_h / 2;
	int screen_mid_y = screen_w / 2;
	int mid_x = (width / 2);
	int mid_y = (height / 2) - 1;

	const Point mid = Point(screen_mid_x, screen_mid_y, 0);
	const Point end = Point(height, width, 0);
	Point current = Point(mid);
	
	points[i] = current;
	i++;
	while (i < count) {
		if (direction == Left) {
			if (current.x > mid.x - limit) {
				current.x -= 1;
			}
		}
		else if (direction == Right) {
			if (current.x < mid.x + limit) {
				current.x += 1;
			}
		}
		else if (direction == Up) {
			if (current.y > mid.y - limit) {
				current.y -= 1;
			}
		}
		else if (direction == Down) {
			if (current.y < mid.y + limit) {
				current.y += 1;
			}
		}

		if (direction == Left && current.x == mid.x - limit) {
			direction = Down;
		}
		else if (direction == Down && current.y == mid.y + limit) {
			direction = Right;
		}
		else if (direction == Right && current.x == mid.x + limit) {
			direction = Up;
		}
		else if (direction == Up && current.y == mid.y - limit) {
			direction = Left;
			limit++;
		}

		current.index = i;
		points[i] = Point(current);
		i++;
	}
}	

bool Mapper::step() {
	pixel_vector->step();
	return complete();
}

bool Mapper::complete() {
	return pixel_vector->complete();
}

int Mapper::getPointCount() {
	return count;
}

Point Mapper::getPoint(int i) {
	return points[i];
}

int Mapper::getFill(int i) {
	int temp = pixel_vector->getFill(i);
	if (temp == 0) {
		return 0;
	}
	else {
		return 255;
	}
}

int Mapper::getFill(int vo, int bo) {
	return pixel_vector->getFill(vo, bo);
}

int Mapper::getFill(Point p) {
	return pixel_vector->getFill(p.index);
}