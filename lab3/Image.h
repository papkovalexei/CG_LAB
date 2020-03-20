#pragma once

#include <iostream>

typedef unsigned char uchar;

class Image
{
public:
	void readFile(std::string filePath);
	void writeFile(std::string filePath);
	void setPixel(bool steep, int x, int y, double color);
	void setPixel(int x, int y);
	uchar* data;	
private:
	int weight, height;
	int pixelFormat;
	int depthPixel;

};