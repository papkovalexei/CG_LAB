#pragma warning(disable : 4996)

#include "Image.h"

void Image::readFile(std::string filePath)
{
	char buffer[16];
	FILE* input_file;

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

	if (buffer[1] != '5')
	{
		std::cerr << "File format not supported" << std::endl;
		exit(1);
	}

	// Start 'skip comment'
	char check_exist_comment = fgetc(input_file);

	if (check_exist_comment == '#')
		while ((check_exist_comment = fgetc(input_file) != '\n'))
			;
	else
		ungetc(check_exist_comment, input_file);
	// End 'skip comment'

	if (fscanf(input_file, "%i %i\n%i\n", &_width, &_height, &_depthPixel) != 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	Image::_data = (uchar*)malloc(Image::_width * Image::_height * sizeof(uchar));

	if (fread(Image::_data, sizeof(uchar), Image::_height * Image::_width, input_file) != Image::_width * Image::_height)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	fclose(input_file);
}

void Image::writeFile(std::string filePath)
{
	FILE* output_file = fopen(filePath.c_str(), "wb");

	fprintf(output_file, "P5\n");

	fprintf(output_file, "%i %i\n%i\n", Image::_width, Image::_height, Image::_depthPixel);

	if (fwrite(Image::_data, sizeof(uchar), Image::_height * Image::_width, output_file) != Image::_width * Image::_height)
	{
		std::cerr << "Error write file" << std::endl;
		fclose(output_file);
		exit(1);
	}

	fclose(output_file);
}

void Image::setPixel(int x, int y, uchar color)
{
	_data[_width * y + x] = color;
}