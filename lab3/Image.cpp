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
	// End 'skip comment'

	if (fscanf(input_file, "%i %i\n%i\n", &weight, &height, &depthPixel) != 3)
	{
		std::cerr << "Error read file" << std::endl;
		exit(1);
	}

	Image::data = (uchar*)malloc(Image::weight * Image::height * sizeof(uchar));

	if (fread(Image::data, sizeof(uchar), Image::height * Image::weight, input_file) != Image::weight * Image::height)
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

	fprintf(output_file, "# Created by Alexei Papkov M3111\n");

	fprintf(output_file, "%i %i\n%i\n", Image::weight, Image::height, Image::depthPixel);

	if (fwrite(Image::data, sizeof(uchar), Image::height * Image::weight, output_file) != Image::weight * Image::height)
	{
		std::cerr << "Error write file" << std::endl;
		fclose(output_file);
		exit(1);
	}

	fclose(output_file);
}

void Image::setPixel(int x, int y, int color)
{
	data[weight * y + x] = color;
}

uchar Image::getPixel(int x, int y)
{
	return data[weight * y + x];
}