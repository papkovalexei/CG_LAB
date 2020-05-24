#include <vector>

#include "Image.h"

void Image::setColorSpace(const ColorSpace& brit)
{
	currectColorSpace = brit;
}

void Image::changeBrit(float offset, float multi)
{
	if (format == P6)
	{
		if (currectColorSpace == YCBCR_CS)
		{
			for (int i = 0; i < _width * _height; i++)
			{
				int answer = (static_cast<float>(_data[i].first) - offset) * multi;

				if (answer > 255)
					answer = 255;
				if (answer < 0)
					answer = 0;
				_data[i].first = answer;
			}
		}
		else
		{
			for (int i = 0; i < _width * _height; i++) 
			{
				int answer = (static_cast<float>(_data[i].first) - offset) * multi;

				if (answer > 255)
					answer = 255;
				if (answer < 0)
					answer = 0;

				_data[i].first = answer;

				answer = (static_cast<float>(_data[i].second) - offset) * multi;

				if (answer > 255)
					answer = 255;
				if (answer < 0)
					answer = 0;

				_data[i].second = answer;

				answer = (static_cast<float>(_data[i].third) - offset) * multi;

				if (answer > 255)
					answer = 255;
				if (answer < 0)
					answer = 0;

				_data[i].third = answer;
			}
		}
	}
	else
	{
		for (int i = 0; i < _width * _height; i++)
		{
			int answer = (static_cast<float>(_data[i].first) - offset) * multi;

			if (answer > 255)
				answer = 255;
			if (answer < 0)
				answer = 0;

			_data[i].first = answer;
			_data[i].second = answer;
			_data[i].third = answer;
		}
	}
}

void Image::autoBrit(bool check)
{
	Answer answer = getDark(check);

	std::cout << "Offset: " << answer.dark << endl
		<< "Multi: " << 255.0 / (static_cast<double>(answer.brit - answer.dark)) << endl;

	changeBrit(answer.dark, 255.0 / (static_cast<double>(answer.brit - answer.dark)));
}

Image::Answer Image::getDark(bool check)
{
	std::vector<int> buffer(256, 0);
	int brit = 0, dark = 0;

	for (int i = 0; i < _width * _height; i++)
	{
		if (format == P6 && currectColorSpace != YCBCR_CS)
		{
			buffer[_data[i].first]++;
			buffer[_data[i].second]++;
			buffer[_data[i].third]++;
		}
		else
			buffer[_data[i].first]++;
	}

	if (check)
	{
		int positionIgnore = 0, ignore = 0, dPos = 0, bPos = 255;

		if (format == P6 && currectColorSpace != YCBCR_CS)
			positionIgnore = static_cast<double>(_width * _height * 3) * PERCENT;
		else
			positionIgnore = static_cast<double>(_width * _height) * PERCENT;

		while (ignore < positionIgnore)
		{
			if (ignore % 2 == 0)
			{
				while (buffer[dPos] == 0)
					dPos++;
				buffer[dPos]--;
				ignore++;
			}
			else
			{
				while (buffer[bPos] == 0)
					bPos++;
				buffer[bPos]--;
				ignore++;
			}
		}
	}

	for (int i = 0; i < 256; i++)
		if (buffer[i] > 0)
		{
			dark = i;
			break;
		}

	for (int i = 255; i >= 0; i--)
		if (buffer[i] > 0)
		{
			brit = i;
			break;
		}

	return Answer{ brit, dark };
}

void Image::writeFile(const string& filePath)
{
	FILE* output_file;

	output_file = fopen(filePath.c_str(), "wb");

	if (format == P6)
		fprintf(output_file, "P6\n");
	else
		fprintf(output_file, "P5\n");

	fprintf(output_file, "%i %i\n%i\n", _width, _height, _depthPixel);

	if (format == P6)
	{
		if (fwrite(_data, sizeof(Data), _height * _width, output_file) != _width * _height)
		{
			std::cerr << "Error write file" << std::endl;
			fclose(output_file);
			exit(1);
		}
	}
	else
	{
		for (int i = 0; i < _height * _width; i++)
			fwrite(&_data[i].first, 1, 1, output_file);
	}

	fclose(output_file);
}

void Image::readFile(const string& filePath)
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

	if (buffer[1] == '6')
		format = P6;
	else if (buffer[1] == '5')
		format = P5;
	else
	{
		std::cerr << "Format not supported" << std::endl;
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
	uchar* _data2 = new uchar[_width * _height];

	if (format == P6)
	{
		if (fread(_data1, sizeof(Data), _height * _width, input_file) != _width * _height)
		{
			std::cerr << "Error read file" << std::endl;
			exit(1);
		}
	}
	else
	{
		if (fread(_data2, sizeof(unsigned char), _height * _width, input_file) != _width * _height)
		{
			std::cerr << "Error read file" << std::endl;
			exit(1);
		}
	}

	_data = new Data[_height * _width];

	for (size_t i = 0; i < _height * _width; i++)
	{
		if (format == P6)
		{
			_data[i].first = _data1[i].first;
			_data[i].second = _data1[i].second;
			_data[i].third = _data1[i].third;
		}
		else
		{
			_data[i].first = _data2[i];
			_data[i].second = _data2[i];
			_data[i].third = _data2[i];
		}
	}

	fclose(input_file);
}