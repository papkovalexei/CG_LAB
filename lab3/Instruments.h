#pragma once

#include "Image.h"

#include <vector>

using namespace std;

struct Vertex
{
	double x;
	double y;

	Vertex(double x_, double y_) : x(x_), y(y_) {}
};

class Instruments : public Image
{
public:
	void drawLine(Vertex vertex_start, Vertex vertex_end, double thickness, double brightness);
private:
	uchar colorCorrection(double x, double y, double transparency, double brightness);
};

