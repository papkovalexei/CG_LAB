#include "Image.h"
#include <cmath>

void swapIntH(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

void WuLine(int x0, int y0, int x1, int y1, float thickness, Image& image)
{
	bool steep = abs(y1 - y0) > abs(x1 - x0);

	if (steep)
	{
		swapIntH(x0, y0);
		swapIntH(x1, y1);
	}

	if (x0 > x1)
	{
		swapIntH(x0, x1);
		swapIntH(y0, y1);
	}

	image.setPixel(steep, x0, y0, 1);
	image.setPixel(steep, x1, y1, 1);

	float dx = x1 - x0;
	float dy = y1 - y0;

	float gradient = dy / dx;
	float y = y0 + gradient;

	for (int x = x0 + 1; x <= x1 - 1; x++)
	{
		for (float temp = y - thickness / 2; temp <= y + thickness / 2; temp += gradient)
		{

			image.setPixel(steep, x, (int)temp, 1 - (temp - (int)temp));
			image.setPixel(steep, x, (int)temp + 1, temp - (int)temp);
		}
		y += gradient;
	}

}

int main(int argc, char** argv)
{
	// lab3.exe file.pnm newFile.pnm x0 y0 x1 y1
	Image image;

	image.readFile(argv[1]);

	WuLine(0, 0, 60, 80, 4, image);

	image.writeFile(argv[2]);

	return 0;
}