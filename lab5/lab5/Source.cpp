#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

#include "ColorSpace.h"

using namespace std;

ColorSpace::Format getFormat(string arg)
{
	if (arg == "RGB")
		return ColorSpace::RGB;

	if (arg == "HSL")
		return ColorSpace::HSL;

	if (arg == "HSV")
		return ColorSpace::HSV;

	if (arg == "CMY")
		return ColorSpace::CMY;

	if (arg == "YCbCr.601")
		return ColorSpace::YCbCr_601;

	if (arg == "YCbCr.709")
		return ColorSpace::YCbCr_709;

	if (arg == "YCoCg")
		return ColorSpace::YCoCg;

	return ColorSpace::NONE;
}

string func(ColorSpace::Format format)
{
	if (format == ColorSpace::CMY)
		return "CMY";
	if (format == ColorSpace::HSL)
		return "HSL";
	if (format == ColorSpace::HSV)
		return "HSV";
	if (format == ColorSpace::RGB)
		return "RGB";
	if (format == ColorSpace::YCbCr_601)
		return "YCbCr.601";
	if (format == ColorSpace::YCbCr_709)
		return "YCbCr.709";
	if (format == ColorSpace::YCoCg)
		return "YCoCg";
}

int main(int argc, char** argv)
{
	if (argc != 11)
	{
		cerr << "Incorrect arguments" << endl;
		return 1;
	}

	ColorSpace image;

	for (int arg_position = 1; arg_position < argc; arg_position++)
	{
		string argument = argv[arg_position];

		if (argument == "-f")
		{
			arg_position++;
			argument = argv[arg_position];

			ColorSpace::Format format = getFormat(argument);

			if (format != ColorSpace::NONE)
				image.setFromColorSpace(format);
			else
			{
				cerr << "Incorrect argument -f" << endl;
				return 1;
			}
		}
		else if (argument == "-t")
		{
			arg_position++;
			argument = argv[arg_position];

			ColorSpace::Format format = getFormat(argument);

			if (format != ColorSpace::NONE)
				image.setToColorSpace(format);
			else
			{
				cerr << "Incorrect argument -t" << endl;
				return 1;
			}
		}
		else if (argument == "-i")
		{
			arg_position++;
			argument = argv[arg_position];

			if (argument == "1")
				image.setMultiInput(false);
			else
				image.setMultiInput(true);

			arg_position++;
			argument = argv[arg_position];

			image.setInputFile(argument);
		}
		else if (argument == "-o")
		{
			arg_position++;
			argument = argv[arg_position];

			if (argument == "1")
				image.setMultiOutput(false);
			else
				image.setMultiOutput(true);

			arg_position++;
			argument = argv[arg_position];

			image.setOutputFile(argument);
		}
	}

	image.readFile();

	cout << "From: " << func(image._from_color_space) << endl;
	cout << "To: " << func(image._to_color_space) << endl;

	image.convert();
	image.writeFile();

	return 0;
}