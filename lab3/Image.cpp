#pragma warning(disable : 4996)

#include "Image.h"

void swapInt(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

void Image::readFile(std::string filePath)
{
	char buffer[16];
	FILE* input_file;

	input_file = fopen(filePath.c_str(), "rb");

	if (!input_file)
	{
		std::cout << "Error open file: " << filePath << std::endl;
		exit(1);
	}

	fgets(buffer, sizeof(buffer), input_file);

	if (buffer[0] != 'P' || strlen(buffer) > 3)
	{
		std::cout << "Error image format" << std::endl;
		exit(1);
	}

	if (buffer[1] != '5')
	{
		std::cout << "File format not supported" << std::endl;
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
		printf("Error read file\n");
		exit(1);
	}

	Image::data = (uchar*)malloc(Image::weight * Image::height * sizeof(uchar));

	if (fread(Image::data, sizeof(uchar), Image::height * Image::weight, input_file) != Image::weight * Image::height)
	{
		printf("Error read file\n");
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
		printf("Error write file\n");
		fclose(output_file);
		exit(1);
	}

	fclose(output_file);
}

double gammaCorrection(double color)
{
	return pow(color, 1.0/2.2);
}

void Image::setPixel(bool steep, int x, int y, double color)
{
	color = gammaCorrection(color);

	if (steep)
	{
		swapInt(x, y);
	}
	uchar color_buffer = 255 - color * 255;

	data[weight * y + x] = color_buffer;
}

void Image::setPixel(int x, int y)
{
	data[weight * y + x] = 0;
}