#include "ColorSpace.h"

void ColorSpace::setInputFile(const string& input_file)
{
	_input_file = input_file;
}

void ColorSpace::setOutputFile(const string& output_file)
{
	_output_file = output_file;
}

void ColorSpace::setFromColorSpace(const Format format)
{
	_from_color_space = format;
}

void ColorSpace::setToColorSpace(const Format format)
{
	_to_color_space = format;
}

void ColorSpace::setMultiInput(bool flag)
{
	_multi_input = flag;
}

void ColorSpace::setMultiOutput(bool flag)
{
	_multi_output = flag;
}

void ColorSpace::readFile()
{
	images[0].readFile(_input_file);

	if (_multi_input)
	{
		_input_file[_input_file.length() - 5] = '2';
		images[1].readFile(_input_file);

		_input_file[_input_file.length() - 5] = '3';
		images[2].readFile(_input_file);
	}
}

void ColorSpace::writeFile()
{
	images[0].writeFile(_output_file);

	if (_multi_output)
	{
		_output_file[_output_file.length() - 5] = '2';
		images[1].writeFile(_output_file);

		_output_file[_input_file.length() - 5] = '3';
		images[3].writeFile(_output_file);
	}
}