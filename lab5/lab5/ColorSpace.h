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

class ColorSpace
{
public:
	enum Format
	{
		RGB = 0,
		HSL = 1,
		HSV = 2,
		YCbCr_601 = 3,
		YCbCr_709 = 4,
		YCoCg = 5,
		CMY = 6,
		NONE = 7
	};

	void setInputFile(const string& input_file);
	void setOutputFile(const string& output_file);
	void setFromColorSpace(const Format format);
	void setToColorSpace(const Format format);
	void setMultiInput(bool flag);
	void setMultiOutput(bool flag);

	void readFile();
	void writeFile();

	void convert();
public:
	void readPGM(const string& filePath1, const string& filePath2, const string& filePath3);
	void readPNM(const string& filePath);

	void writePGM(const string& filePath1, const string& filePath2, const string& filePath3);
	void writePNM(const string& filePath);

	string _input_file;
	string _output_file;
	Format _from_color_space;
	Format _to_color_space;
	bool _multi_input;
	bool _multi_output;

	Data* _data;
	int _width;
	int _height;
	int _depthPixel;
};

