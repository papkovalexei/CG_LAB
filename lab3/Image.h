#pragma once

#include <iostream>

typedef unsigned char uchar;

class Image
{
public:
	void readFile(std::string filePath);
	void writeFile(std::string filePath);

	void setPixel(int x, int y, int color);
	uchar getPixel(int x, int y);
private:
	int weight, height;
	int pixelFormat;
	int depthPixel;
protected:
	uchar* data;
};