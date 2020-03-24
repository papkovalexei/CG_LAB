#pragma once

#include "Image.h"

#include <vector>

using namespace std;

struct Normal
{
	int x0, y0;
	int x1, y1;
};

class Instruments : public Image
{
public:
	void drawLine(int x0, int y0, int x1, int y1, double width, double color);
	void drawLine(int x0, int y0, int x1, int y1, double color, vector<pair<int, int>>& array);
	void setGamma(double gamma1)
	{
		gamma = gamma1;
	}
private:
	void stairsLine(int x0, int y0, int x1, int y1, double color);
	void line(int x0, int y0, int x1, int y1, double color);
	uchar colorCorrection(double color, int x, int y);
	double gamma = 2.2;
};

