#pragma warning(disable : 4996)

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

void ColorSpace::readPGM(const string& filePath1, const string& filePath2, const string& filePath3)
{
	FILE *input_file1, *input_file2, *input_file3;
	char buffer1[16], buffer2[16], buffer3[16];

	input_file1 = fopen(filePath1.c_str(), "rb");
	input_file2 = fopen(filePath2.c_str(), "rb");
	input_file3 = fopen(filePath3.c_str(), "rb");

	if (!input_file1)
	{
		std::cerr << "Error open file: " << filePath1 << std::endl;
		exit(1);
	}

	if (!input_file2)
	{
		std::cerr << "Error open file: " << filePath2 << std::endl;
		exit(1);
	}

	if (!input_file3)
	{
		std::cerr << "Error open file: " << filePath3 << std::endl;
		exit(1);
	}

	fgets(buffer1, sizeof(buffer1), input_file1);
	fgets(buffer2, sizeof(buffer2), input_file2);
	fgets(buffer3, sizeof(buffer3), input_file3);

	if ((buffer1[0] != 'P' || strlen(buffer1) > 3) && (buffer2[0] != 'P' || strlen(buffer2) > 3) && (buffer3[0] != 'P' || strlen(buffer3) > 3))
	{
		std::cerr << "Error image format" << std::endl;
		exit(1);
	}

	if ((buffer1[1] != '5') && (buffer2[1] != '5') && (buffer3[1] != '5'))
	{
		std::cerr << "File format not supported" << std::endl;
		exit(1);
	}

	char check_exist_comment = fgetc(input_file1);

	if (check_exist_comment == '#')
		while ((check_exist_comment = fgetc(input_file1) != '\n'))
			;
	else
		ungetc(check_exist_comment, input_file1);

	check_exist_comment = fgetc(input_file2);

	if (check_exist_comment == '#')
		while ((check_exist_comment = fgetc(input_file2) != '\n'))
			;
	else
		ungetc(check_exist_comment, input_file2);

	check_exist_comment = fgetc(input_file3);

	if (check_exist_comment == '#')
		while ((check_exist_comment = fgetc(input_file3) != '\n'))
			;
	else
		ungetc(check_exist_comment, input_file3);

	if (fscanf(input_file1, "%i %i\n%i\n", &_width, &_height, &_depthPixel) != 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	if (fscanf(input_file2, "%i %i\n%i\n", &_width, &_height, &_depthPixel) != 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	if (fscanf(input_file3, "%i %i\n%i\n", &_width, &_height, &_depthPixel) != 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	uchar* _data1 = new uchar[_width * _height];
	uchar* _data2 = new uchar[_width * _height];
	uchar* _data3 = new uchar[_width * _height];

	if (fread(_data1, sizeof(uchar), _height * _width, input_file1) != _width * _height)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	if (fread(_data2, sizeof(uchar), _height * _width, input_file2) != _width * _height)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	if (fread(_data3, sizeof(uchar), _height * _width, input_file3) != _width * _height)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	for (size_t i = 0; i < _height * _width; i++)
	{
		ColorSpace::_data[i].first = _data1[i];
		ColorSpace::_data[i].second = _data2[i];
		ColorSpace::_data[i].third = _data3[i];
	}

	fclose(input_file1);
	fclose(input_file2);
	fclose(input_file3);
}

void ColorSpace::readPNM(const string& filePath)
{
	FILE* input_file;
	char buffer[16];

	input_file = fopen(filePath.c_str(), "rb");

	if (!input_file)
	{
		std::cerr << "Error open file: " << filePath << std::endl;
		exit(1);
	}

	
	fgets(buffer, sizeof(buffer), input_file);

	if (buffer[0] != 'P' || strlen(buffer) > 3)
	{
		std::cerr << "Error image format" << std::endl;
		exit(1);
	}

	if (buffer[1] != '6')
	{
		std::cerr << "File format not supported" << std::endl;
		exit(1);
	}

	char check_exist_comment = fgetc(input_file);

	if (check_exist_comment == '#')
		while ((check_exist_comment = fgetc(input_file) != '\n'))
			;
	else
		ungetc(check_exist_comment, input_file);

	if (fscanf(input_file, "%i %i\n%i\n", &_width, &_height, &_depthPixel) != 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	Data* _data1 = new Data[_width * _height];

	if (fread(_data1, sizeof(Data), _height * _width, input_file) != _width * _height * 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	for (size_t i = 0; i < _height * _width; i++)
	{
		ColorSpace::_data[i].first = _data[i].first;
		ColorSpace::_data[i].second = _data[i].second;
		ColorSpace::_data[i].third = _data[i].third;
	}

	fclose(input_file);
}

void ColorSpace::writePGM(const string& filePath1, const string& filePath2, const string& filePath3)
{
	FILE* output_file1, * output_file2, * output_file3;

	output_file1 = fopen(filePath1.c_str(), "wb");
	output_file2 = fopen(filePath2.c_str(), "wb");
	output_file3 = fopen(filePath3.c_str(), "wb");

	fprintf(output_file1, "P6\n");
	fprintf(output_file2, "P6\n");
	fprintf(output_file3, "P6\n");

	fprintf(output_file1, "%i %i\n%i\n", _width, _height, _depthPixel);
	fprintf(output_file2, "%i %i\n%i\n", _width, _height, _depthPixel);
	fprintf(output_file3, "%i %i\n%i\n", _width, _height, _depthPixel);

	for (size_t i = 0; i < _height * _width; i++)
	{
		fwrite(&_data[i].first, 1, 1, output_file1);
		fwrite(&_data[i].second, 1, 1, output_file2);
		fwrite(&_data[i].third, 1, 1, output_file3);
	}

	fclose(output_file1);
	fclose(output_file2);
	fclose(output_file3);
}

void ColorSpace::writePNM(const string& filePath)
{
	FILE* output_file;

	output_file = fopen(filePath.c_str(), "wb");

	fprintf(output_file, "P6\n");

	fprintf(output_file, "%i %i\n%i\n", _width, _height, _depthPixel);

	if (fwrite(_data, sizeof(Data), _height * _width, output_file) != _width * _height * 3)
	{
		std::cerr << "Error write file" << std::endl;
		fclose(output_file);
		exit(1);
	}

	fclose(output_file);
}

void ColorSpace::readFile()
{
	if (_multi_input)
	{
		_input_file.insert(_input_file.length() - 4, "_1");

		string filePath1, filePath2, filePath3;

		filePath1 = _input_file;

		_input_file.replace(_input_file.length() - 5, 1, "2");
		filePath2 = _input_file;

		_input_file.replace(_input_file.length() - 5, 1, "3");
		filePath3 = _input_file;

		readPGM(filePath1, filePath2, filePath3);
	}
	else
		readPNM(_input_file);
}

void ColorSpace::writeFile()
{
	if (_multi_output)
	{
		_output_file.insert(_output_file.length() - 4, "_1");

		string filePath1, filePath2, filePath3;

		filePath1 = _output_file;

		_output_file.replace(_output_file.length() - 5, 1, "2");
		filePath2 = _output_file;

		_output_file.replace(_output_file.length() - 5, 1, "3");
		filePath3 = _output_file;

		writePGM(filePath1, filePath2, filePath3);
	}
	else
		writePNM(_output_file);
}

void ColorSpace::convertToRGB()
{
	switch (_from_color_space)
	{
	case RGB: // done
		break;
	case CMY: // done
		for (size_t i = 0; i < _height * _width; i++)
		{
			_data[i].first = 255 - _data[i].first;
			_data[i].second = 255 - _data[i].second;
			_data[i].third = 255 - _data[i].third;
		}
		break;
	case HSL: // done
	case HSV: // done
		for (size_t i = 0; i < _height * _width; i++)
		{
			double H, S, V;
			double R, G, B;

			H = ((double)_data[i].first / 255) * 360;
			S = _data[i].second;
			V = _data[i].third;

			double C = V * S;
			double X = C * (1 - abs(fmod(H / 60, 2) - 1));
			double M = V - C;

			if (_from_color_space == HSL)
			{
				C = (1 - abs(2 * V - 1)) * S;
				X = C * (1 - abs(fmod(H / 60, 2) - 1));
				M = (V - C) / 2;
			}

			if (0 <= H && H < 60)
			{
				R = C;
				G = X;
				B = 0;
			}
			else if (60 <= H && H < 120)
			{
				R = X;
				G = C;
				B = 0;
			}
			else if (120 <= H && H < 180)
			{
				R = 0;
				G = C;
				B = X;
			}
			else if (180 <= H && H < 240)
			{
				R = 0;
				G = X;
				B = C;
			}
			else if (240 <= H && H < 300)
			{
				R = X;
				G = 0;
				B = C;
			}
			else if (300 <= H && H < 360)
			{
				R = C;
				G = 0;
				B = X;
			}

			_data[i].first = (R + M) * 255;
			_data[i].second = (G + M) * 255;
			_data[i].third = (B + M) * 255;
		}
		break;
	case YCbCr_601: // done
	case YCbCr_709: // done
		double Kr = 0.0722, Kg = 0.2126, Kb = 0.7152;

		if (_from_color_space == YCbCr_601)
		{
			Kr = 0.299;
			Kg = 0.587;
			Kb = 0.114;
		}

		for (size_t i = 0; i < _width * _height; i++)
		{
			double Y, Cb, Cr;
			double R, G, B;

			Y = _data[i].first / 255;
			Cb = _data[i].second / 255 - 0.5;
			Cb = _data[i].third / 255 - 0.5;

			R = (Y + Cr * (2.0 - 2.0 * Kr));
			G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
			B = (Y + (2.0 - 2.0 * Kb) * Cb);

			if (R < 0)
				R = 0;
			else if (R > 1)
				R = 1;

			if (G < 0)
				R = 0;
			else if (G > 1)
				G = 1;

			if (B < 0)
				B = 0;
			else if (B > 1)
				B = 1;

			_data[i].first = R * 255;
			_data[i].second = G * 255;
			_data[i].third = B * 255;
		}
		break;
	case YCoCg: // done
		for (size_t i = 0; i < _width * _height; i++)
		{
			double Y, Co, Cg;
			double R, G, B;

			Y = _data[i].first / 255.0;
			Co = _data[i].second / 255.0 - 0.5;
			Cg = _data[i].third / 255.0 - 0.5;

			R = Y + Co - Cg;
			G = Y + Cg;
			B = Y - Co - Cg;

			if (R < 0)
				R = 0;
			else if (R > 1)
				R = 1;

			if (G < 0)
				R = 0;
			else if (G > 1)
				G = 1;

			if (B < 0)
				B = 0;
			else if (B > 1)
				B = 1;

			_data[i].first = R * 255.0;
			_data[i].second = G * 255.0;
			_data[i].third = B * 255.0;
		}
		break;
	default:
		break;
	}
}

void convert()
{
	
}