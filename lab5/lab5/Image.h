#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

typedef unsigned char uchar;

class Image
{
public:
	void readFile(std::string filePath);
	void writeFile(std::string filePath);
	void setPixel(int x, int y, uchar color);
private:
	enum Format
	{
		P5 = 0,
		P6 = 1
	};

	int _pixelFormat;
	int _depthPixel;
	int _width, _height;

	Format _image_format;
	size_t _size_data;
	uchar* _data;
};