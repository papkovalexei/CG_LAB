#include "Instruments.h"

void swapIntH(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

uchar Instruments::colorCorrection(double color, int x, int y)
{
	return (255 - pow(color, 1.0 / gamma) * 255);
}

void Instruments::stairsLine(int x0, int y0, int x1, int y1, double color)
{
	bool steep = abs(y1 - y0) >abs(x1 - x0); 
	
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

	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int error = dx / 2; 
	int ystep = (y0 < y1) ? 1 : -1; 
	int y = y0;

	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			setPixel(y, x, colorCorrection(color, y, x));
		else
			setPixel(x, y, colorCorrection(color, x, y));

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Instruments::line(int x0, int y0, int x1, int y1, double color)
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

	if (steep)
	{
		setPixel(y0, x0, colorCorrection(color, y0, x0));
		setPixel(y1, x1, colorCorrection(color, y1, x1));
	}
	else
	{
		setPixel(x0, y0, colorCorrection(color, x0, y0));
		setPixel(x1, y1, colorCorrection(color, x1, y1));
	}

	double dx = x1 - x0;
	double dy = y1 - y0;

	double gradient = dy / dx;
	double y = y0 + gradient;

	for (int x = x0 + 1; x <= x1 - 1; x++)
	{
		if (steep)
		{
			setPixel((int)y, x, colorCorrection(color, (int)y, x) + colorCorrection(1 - (y - (int)y), (int)y, x));
			setPixel((int)y + 1, x, colorCorrection(color, (int)y + 1, x) + colorCorrection(y - (int)y, (int)y + 1, x));
		}
		else
		{
			setPixel(x, (int)y, colorCorrection(color, x, (int)y) + colorCorrection(1 - (y - (int)y), x, (int)y));
			setPixel(x, (int)y + 1, colorCorrection(color, x, (int)y + 1) + colorCorrection(y - (int)y, x, (int)y + 1));
		}
		y += gradient;
	}
}

Normal createNormal(int x0, int y0, int x1, int y1, double width)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	if (dx == 0)
	{
		Normal v;

		v.x0 = x0;
		v.x1 = x0 + width - 1;
		v.y0 = y1;
		v.y1 = y1;

		return v;
	}

	if (dy == 0)
	{
		Normal v;

		v.x0 = x0;
		v.x1 = x0;
		v.y0 = y0;
		v.y1 = y1 + width - 1;

		return v;
	}

	double k = (double)(-dy) / (double)(-dx);
	double b = (double)(-(x1 * y0) + (y1 * x0)) / (double)(-dx);

	double vertexX1 = ((double)y1 + 1.0f / k * (double)x1 - b - (width-1) * sqrt(pow(k, 2) + 1.0f)) * k / (pow(k, 2) + 1.0f);
	double vertexX0 = ((double)y1 + 1.0f / k * (double)x1 - b + (width-1) * sqrt(pow(k, 2) + 1.0f)) * k / (pow(k, 2) + 1.0f);

	double vertexY1 = -1.0f / k * vertexX1 + ((double)y1 + (1.0f / k * (double)x1));
	double vertexY0 = -1.0f / k * vertexX0 + ((double)y1 + (1.0f / k * (double)x1));

	Normal v;

	v.x0 = (int)floor(vertexX0);
	v.x1 = (int)floor(vertexX1);
	v.y0 = (int)floor(vertexY0);
	v.y1 = (int)floor(vertexY1);

	return v;
}

void Instruments::drawLine(int x0, int y0, int x1, int y1, double color, vector<pair<int, int>>& array)
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

	if (steep)
	{
		setPixel(y0, x0, colorCorrection(color, y0, x0));
		setPixel(y1, x1, colorCorrection(color, y1, x1));
		array.push_back(pair<int, int>(y0, x0));
		array.push_back(pair<int, int>(y1, x1));
	}
	else
	{
		setPixel(x0, y0, colorCorrection(color, x0, y0));
		setPixel(x1, y1, colorCorrection(color, x1, y1));

		array.push_back(pair<int, int>(x0, y0));
		array.push_back(pair<int, int>(x1, y1));
	}

	double dx = x1 - x0;
	double dy = y1 - y0;

	double gradient = dy / dx;
	double y = y0 + gradient;

	for (int x = x0 + 1; x <= x1 - 1; x++)
	{
		if (steep)
		{
			setPixel((int)y, x, colorCorrection(color, (int)y, x) - colorCorrection(y - (int)y, (int)y, x));
			setPixel((int)y + 1, x, colorCorrection(color, (int)y + 1, x) + colorCorrection(y - (int)y, (int)y + 1, x));
			array.push_back(pair<int, int>((int)y, x));
			array.push_back(pair<int, int>((int)y + 1, x));
		}
		else
		{
			setPixel(x, (int)y, colorCorrection(color, x, (int)y) - colorCorrection(y - (int)y, x, (int)y));
			setPixel(x, (int)y + 1, colorCorrection(color, x, (int)y + 1) + colorCorrection(y - (int)y, x, (int)y + 1));
			array.push_back(pair<int, int>(x, (int)y));
			array.push_back(pair<int, int>(x, (int)y + 1));
		}
		y += gradient;
	}
}

void Instruments::drawLine(int x0, int y0, int x1, int y1, double width, double color)
{
	if (width > 1)
	{
		Normal vertex1 = createNormal(x0, y0, x1, y1, width);
		Normal vertex2 = createNormal(x1, y1, x0, y0, width);

		vector<pair<int, int>> array_points_n1;
		vector<pair<int, int>> array_points_n2;

		drawLine(vertex1.x0, vertex1.y0, vertex1.x1, vertex1.y1, color, array_points_n1);
		drawLine(vertex2.x0, vertex2.y0, vertex2.x1, vertex2.y1, color, array_points_n2);

		line(vertex1.x0, vertex1.y0, vertex2.x0, vertex2.y0, color);
		line(vertex2.x1, vertex2.y1, vertex1.x1, vertex1.y1, color);

		for (int i = 0; i < array_points_n1.size(); i++)
		{
			int vertex_x, toVertex_x, vertex_y, toVertex_y;

			vertex_x = array_points_n1[i].first;
			vertex_y = array_points_n1[i].second;

			toVertex_x = array_points_n2[i].first;
			toVertex_y = array_points_n2[i].second;

			stairsLine(vertex_x, vertex_y, toVertex_x, toVertex_y, color);
		}
	}
	else
		line(x0, y0, x1, y1, color);
}