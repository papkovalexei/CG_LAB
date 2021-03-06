#pragma once

#include <iostream>
#include <algorithm>

typedef unsigned char uchar;

class Image
{
public:
	void readFile(std::string filePath);
	void writeFile(std::string filePath);

	void setPixel(int x, int y, uchar color);
private:
	int _pixelFormat;
	int _depthPixel;
protected:
	int _width, _height;
	uchar* _data;
};