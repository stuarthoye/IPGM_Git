#include "PixelVector.h"
#include <iostream>
#include <climits>

using namespace std;

PixelVector::PixelVector(int width, int height)
{
	int_size = sizeof(unsigned int) * CHAR_BIT;
	pixel_count = width * height;
	int_count = (pixel_count / int_size) + 1;
	vector = new unsigned int[int_count];
	for (int i = 0; i < int_count; i++) {
		vector[i] = 0;
	}
}

PixelVector::~PixelVector()
{
	delete[] vector;
}

int PixelVector::getFill(int index) {
	int vector_offset = index / int_size;
	int bit_offset = index % int_size;
	if ((((vector[vector_offset]) >> bit_offset) & 1) == 0) {
		return 0;
	}
	else {
		return 255;
	}
}

int PixelVector::getFill(int vector_offset, int bit_offset) {
	if ((((vector[vector_offset]) >> bit_offset) & 1) == 0) {
		return 0;
	}
	else {
		return 255;
	}
}

int PixelVector::getCount() {
	return pixel_count;
}

void PixelVector::step() {
	if (vector[0] == -1) {
		vector[0] = 0;
		overflow(1);
	} 
	else {
		vector[0]++;
	}
}

void PixelVector::overflow(int i) {
	if (vector[i] == -1) {
		vector[i] = 0;
		overflow(i + 1);
	}
	else {
		vector[i]++;
	}
}

bool PixelVector::complete() {
	for (int i = pixel_count - 1; i >= 0; i--) {
		if (vector[i] != -1) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}