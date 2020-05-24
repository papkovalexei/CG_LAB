#pragma once
#include <string>
#include <iostream>

using namespace std;

typedef unsigned char uchar;

struct Data
{
	uchar first;
	uchar second;
	uchar third;
};

enum Brit {
	RGB = 0,
	YCBCR = 1,
	RGB_AUTO = 2,
	YCBCR_AUTO = 3,
	RGB_AUTO_PLUS = 4,
	YCBCR_AUTO_PLUS = 5
};

enum ColorSpace
{
	RGB_CS = 0,
	YCBCR_CS = 1
};

class Image
{
public:
	void readFile(const string& filePath);
	void writeFile(const string& filePath);

	void setColorSpace(const ColorSpace& cs);
	void changeBrit(float offset, float multi);
	void autoBrit(bool check);

private:
	struct Answer
	{
		int brit;
		int dark;

		Answer(int _brit, int _dark) : brit(_brit), dark(_dark) {}
		Answer() {}
	};

	const float PERCENT = 0.0039;
	Answer getDark(bool check);

	ColorSpace currectColorSpace;
	Data* _data;
	int _width;
	int _height;
	int _depthPixel;

	enum Format
	{
		P5, P6
	}format;
};

