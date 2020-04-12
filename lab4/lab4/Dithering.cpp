#include "Dithering.h"

#include <ctime>
#include <vector>

void Dithering::drawGradient()
{
    for (int y = 0; y < _height; y++)
        for (int x = 0; x < _width; x++)
            _data[y * _width + x] = colorCorrect(static_cast<double>(x) / _width * 255.0);
}

double Dithering::nearestColor(double color)
{
    color /= 255;

    if (gamma == 0)
        return color < 0.04045 ? (255 * color) / 12.92 : 255 * (pow((200.0 * color + 11.0) / 211.0, 2.4));
    else
        return 255 * pow(color, 1 / gamma);
}

double Dithering::colorCorrect(double color)
{
    color /= 255;
    if (color > 1)
        color = 1;

    if (gamma == 0)
        return color < 0.0031308 ? color * 12.92 * 255 : 255 * ((211.0 * pow(color, 0.4166) - 11.0) / 200.0);    
    else 
        return 255 * pow(color, gamma);
}

void Dithering::dithering(DITHERING_TYPE type)
{
    int power = pow(2, bit);
    vector<double> translateError(_width * _height);

	switch (type)
	{
    case Dithering::NONE:
        break;
    case Dithering::ORDERED:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = ((nearestColor(_data[y * _width + x]) + (255 / bit)) * (ORDERED_MATRIX[y % 8][x % 8] - 0.5)) / 255.0;

                if (bufferColor < 0)
                    bufferColor = 0;

                bufferColor = round(bufferColor * (power - 1));

                _data[y * _width + x] = round(colorCorrect(bufferColor * (255 / (power - 1))));
            }
        break;
    case Dithering::RANDOM:
        srand(time(0));

        for (int i = 0; i < _height * _width; i++)
        {
            double bufferColor = ((nearestColor(_data[i]) + (255/bit)) * (static_cast<double>(rand()/ 32767.0) - 0.75)) / 255.0;

            if (bufferColor < 0)
                bufferColor = 0;
            bufferColor = round(bufferColor * (power - 1));

            _data[i] = round(colorCorrect(bufferColor * (255 / (power - 1))));
        }
        break;
    case Dithering::FLOYD_STEINBERG:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = (nearestColor(_data[y * _width + x]) + translateError[y * _width + x]) / 255.0;

                bufferColor = round(bufferColor * (power - 1));
                bufferColor *= 255 / (power - 1);

                double error = _data[y * _width + x] + translateError[y * _width + x] - bufferColor;
                _data[y * _width + x] = bufferColor;

                if (x + 1 < _width)
                    translateError[y * _width + x + 1] += error;

                if (y + 1 < _height)
                {
                    if (x + 1 < _width)
                        translateError[(y + 1) * _width + x + 1] += error * 1.0 / 16.0;
                    translateError[(y + 1) * _width + x] += error * 5.0 / 15.0;

                    if (y - 1 > 0 && x - 1 > 0)
                        translateError[(y - 1) * _width + x - 1] += error * 3.0 / 15.0;
                }
            }
        break;
    case Dithering::JARVIS_JUDICE_NINKE:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = (nearestColor(_data[y * _width + x]) + translateError[y * _width + x]) / 255.0;
                bufferColor = round(bufferColor * (power - 1));
                bufferColor *= 255 / (power - 1);

                double error = _data[y * _width + x] + translateError[y * _width + x] - bufferColor;
                _data[y * _width + x] = bufferColor;

                for (int temp = 0; temp <= 2; temp++)
                    for (int temp_1 = -2; temp_1 <= 2; temp_1++)
                    {
                        if (y + temp < _height)
                        {
                            if (temp == 0 && temp_1 > 0)
                            {
                                if (x + temp_1 < _width)
                                    translateError[(y + temp) * _width + x + temp_1] += error * JARVIS_JUDICE_NINKE_MATRIX[temp][temp_1 + 2] / 48.0;
                            }
                            else
                            {
                                if (x + temp_1 < _width && x + temp_1 > 0)
                                    translateError[(y + temp) * _width + x + temp_1] += error * JARVIS_JUDICE_NINKE_MATRIX[temp][temp_1 + 2] / 48.0;
                            }
                        }
                    }
            }
        break;
    case Dithering::SIERRA:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = (nearestColor(_data[y * _width + x]) + translateError[y * _width + x]) / 255.0;
                bufferColor = round(bufferColor * (power - 1));
                bufferColor *= 255 / (power - 1);

                double error = _data[y * _width + x] + translateError[y * _width + x] - bufferColor;
                _data[y * _width + x] = bufferColor;

                for (int temp = 0; temp <= 2; temp++)
                    for (int temp_1 = -2; temp_1 <= 2; temp_1++)
                    {
                        if (y + temp < _height)
                        {
                            if (temp == 0 && temp_1 > 0)
                            {
                                if (x + temp_1 < _width)
                                    translateError[(y + temp) * _width + x + temp_1] += error * SIERRA_MATRIX[temp][temp_1 + 2] / 32.0;
                            }
                            else
                            {
                                if (x + temp_1 < _width && x + temp_1 > 0)
                                    translateError[(y + temp) * _width + x + temp_1] += error * SIERRA_MATRIX[temp][temp_1 + 2] / 32.0;
                            }
                        }
                    }
            }
        break;
    case Dithering::ATKINSOM:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = (nearestColor(_data[y * _width + x]) + translateError[y * _width + x]) / 255.0;
                bufferColor = round(bufferColor * (power - 1));
                bufferColor *= 255 / (power - 1);

                double error = _data[y * _width + x] + translateError[y * _width + x] - bufferColor;
                _data[y * _width + x] = bufferColor;

                for (int temp = 0; temp <= 2; temp++)
                    for (int temp_1 = -2; temp_1 <= 2; temp_1++)
                    {
                        if (y + temp < _height)
                        {
                            if (temp == 0 && temp_1 > 0)
                            {
                                if (x + temp_1 < _width)
                                    translateError[(y + temp) * _width + x + temp_1] += error * ATKINSON_MATRIX[temp][temp_1 + 2] / 8.0;
                            }
                            else
                            {
                                if (x + temp_1 < _width && x + temp_1 > 0)
                                    translateError[(y + temp) * _width + x + temp_1] += error * ATKINSON_MATRIX[temp][temp_1 + 2] / 8.0;
                            }
                        }
                    }
            }
        break;
    case Dithering::HALFTONE:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = ((nearestColor(_data[y * _width + x]) + (255 / bit)) * (HALFTONE_MATRIX[y % 4][x % 4] - 0.75)) / 255.0;

                if (bufferColor < 0)
                    bufferColor = 0;

                bufferColor = round(bufferColor * (power - 1));

                _data[y * _width + x] = round(colorCorrect(bufferColor * (255 / (power - 1))));
            }
        break;
    default:
        break;
	}
}
