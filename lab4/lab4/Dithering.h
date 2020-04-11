#pragma once

#include "Image.h"

class Dithering : public Image
{
public:
	enum DITHERING_TYPE { NONE, ORDERED, RANDOM, FLOYD_STEINBERG, 
							JARVIS_JUDICE_NINKE, SIERRA, ATKINSOM, HALFTONE };

	void dithering(DITHERING_TYPE type);

	void setGamma(double gamma) { this->gamma = gamma; }
	void setBit(unsigned short bit) { this->bit = bit; }
private:
	double nearestColor(double color);
	double colorCorrect(double color);

	double gamma;
	unsigned short bit;

	const double ordered_matrix[8][8] = {
	{0.0 / 64.0, 48.0 / 64.0, 12.0 / 64.0, 60.0 / 64.0, 3.0 / 64.0, 51.0 / 64.0, 15.0 / 64.0, 63.0 / 64.0},
	{32.0 / 64.0, 16.0 / 64.0, 44.0 / 64.0, 28.0 / 64.0, 35.0 / 64.0, 19.0 / 64.0, 47.0 / 64.0, 31.0 / 64.0},
	{8.0 / 64.0, 56.0 / 64.0, 4.0 / 64.0, 52.0 / 64.0, 11.0 / 64.0, 59.0 / 64.0, 7.0 / 64.0, 55.0 / 64.0},
	{40.0 / 64.0, 24.0 / 64.0, 36.0 / 64.0, 20.0 / 64.0, 43.0 / 64.0, 27.0 / 64.0, 39.0 / 64.0, 23.0 / 64.0},
	{2.0 / 64.0, 50.0 / 64.0, 14.0 / 64.0, 62.0 / 64.0, 1.0 / 64.0, 49.0 / 64.0, 13.0 / 64.0, 61.0 / 64.0},
	{34.0 / 64.0, 18.0 / 64.0, 46.0 / 64.0, 30.0 / 64.0, 33.0 / 64.0, 17.0 / 64.0, 45.0 / 64.0, 29.0 / 64.0},
	{10.0 / 64.0, 58.0 / 64.0, 6.0 / 64.0, 54.0 / 64.0, 9.0 / 64.0, 57.0 / 64.0, 5.0 / 64.0, 53.0 / 64.0},
	{42.0 / 64.0, 26.0 / 64.0, 38.0 / 64.0, 22.0 / 64.0, 41.0 / 64.0, 25.0 / 64.0, 37.0 / 64.0, 21.0 / 64.0},
	};
	const double halftone_matrix[4][4] = {
		{13.0 / 16.0, 11.0 / 16.0, 4.0 / 16.0, 8.0 / 16.0},
		{6.0 / 16.0, 0, 3.0 / 16.0, 15.0 / 16.0},
		{14.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 7.0 / 16.0},
		{9.0 / 16.0, 5.0 / 16.0, 10.0 / 16.0, 12.0 / 16.0},
	};
};

