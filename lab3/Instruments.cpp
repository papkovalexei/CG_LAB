#include "Instruments.h"

double distance(Vertex a, Vertex b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

uchar Instruments::colorCorrection(double x, double y, double transparency, double brightness)
{
	if (y < 0 || y >= _height || x < 0 || x >= _width)
		throw exception("Incorrect coord");

	transparency = max(0.0, min(1.0, transparency));

	double lineColor = brightness / 255.0;
	int y1 = y, x1 = x;
	double sRGBColor = _data[y1 * _width + x1] / 255.0;
	double imageLineColor = sRGBColor <= 0.04045 ? sRGBColor / 12.92 : pow((sRGBColor + 0.055) / 1.055, 2.4);
	double color = (1 - transparency) * lineColor + transparency * imageLineColor;
	double sRGBc = color <= 0.0031308 ? 12.92 * color : 1.055 * pow(color, 1 / 2.4) - 0.055;

	return 255 * sRGBc;
}

void Instruments::drawLine(Vertex vertex_start, Vertex vertex_end, double thickness, double brightness)
{
	if (thickness <= 0)
		throw exception("Incorrect thickness");

	bool steep = abs(vertex_start.y - vertex_end.y) > abs(vertex_start.x - vertex_end.x);

	if (steep)
	{
		swap(vertex_start.x, vertex_start.y);
		swap(vertex_end.x, vertex_end.y);
	}

	if (vertex_start.x > vertex_end.x)
	{
		swap(vertex_start.x, vertex_end.x);
		swap(vertex_start.y, vertex_end.y);
	}

	double dx = vertex_end.x - vertex_start.x;
	double dy = vertex_end.y - vertex_start.y;
	double gradient = dy / dx;

	double y = vertex_start.y + gradient * (round(vertex_start.x) - vertex_start.x);

	for (int x = round(vertex_start.x); x < round(vertex_end.x); x++)
	{
		for (int tempY = (int)(y - ((thickness - 1) / 2)); tempY <= (int)(y - ((thickness - 1) / 2) + thickness); tempY++)
		{
			if (steep)
				setPixel(tempY, x, colorCorrection(tempY, x, 1 - min(1.0, (thickness + 1.0) / 2.0 - fabs(y - tempY)), brightness));
			else
				setPixel(x, tempY, colorCorrection(x, tempY, 1 - min(1.0, (thickness + 1.0) / 2.0 - fabs(y - tempY)), brightness));
		}
		y += gradient;
	}

	Vertex start = { round(vertex_start.x), round(vertex_start.y) };
	Vertex end = { round(vertex_end.x), round(vertex_end.y) };

	for (int tempX = start.x - thickness / 2; tempX <= start.x; tempX++)
	{
		y = vertex_start.y + gradient * (tempX - vertex_start.x);

		for (int tempY = (int)(y - (thickness - 1) / 2.0); tempY <= (int)(y - (thickness - 1) / 2.0 + thickness); tempY++)
		{
			if (steep)
				setPixel(tempY, tempX, colorCorrection(tempY, tempX, 1 - min(1.0, (thickness + 0.5) / 2.0 - distance({ (double)(tempX), (double)(tempY) }, { start.x, start.y })), brightness));
			else
				setPixel(tempX, tempY, colorCorrection(tempX, tempY, 1 - min(1.0, (thickness + 0.5) / 2.0 - distance({ (double)(tempX), (double)(tempY) }, { start.x, start.y })), brightness));
		}
	}

	for (int tempX = end.x; tempX <= end.x + thickness / 2; tempX++)
	{
		y = vertex_start.y + gradient * (tempX - vertex_start.x);

		for (int tempY = (int)(y - (thickness - 1) / 2.0); tempY <= (int)(y - (thickness - 1) / 2.0 + thickness); tempY++)
		{
			if (steep)
				setPixel(tempY, tempX, colorCorrection(tempY, tempX, 1 - min(1.0, (thickness + 0.5) / 2.0 - distance({ (double)(tempX), (double)(tempY) }, { end.x, end.y })), brightness));
			else
				setPixel(tempX, tempY, colorCorrection(tempX, tempY, 1 - min(1.0, (thickness + 0.5) / 2.0 - distance({ (double)(tempX), (double)(tempY) }, { end.x, end.y })), brightness));
		}
	}
}