#pragma once
#include "Image.h"

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

	ColorSpace() 
	{
		images = new Image[3];
	}
	~ColorSpace()
	{
		delete[] images;
	}

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
	string _input_file;
	string _output_file;
	Format _from_color_space;
	Format _to_color_space;
	bool _multi_input;
	bool _multi_output;

	Image* images;
};

