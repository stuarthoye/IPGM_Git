#pragma once

class PixelVector
{
public:
	PixelVector(int width, int height);
	~PixelVector();
	int getFill(int index);
	int getFill(int vo, int bo);
	int getCount();
	void step();
	void overflow(int index);
	bool complete();

private:
	int pixel_count, int_count, int_size;
	unsigned int *vector;
};
