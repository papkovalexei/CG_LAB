#include "Dithering.h"

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

	switch (type)
	{
    case Dithering::NONE:
        break;
    case Dithering::ORDERED:
        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {
                double bufferColor = ((nearestColor(_data[y * _width + x]) + (255 / bit)) * (ordered_matrix[y % 8][x % 8] - 0.5)) / 255;

                if (bufferColor < 0)
                    bufferColor = 0;

                bufferColor = round(bufferColor * (power - 1));

                _data[y * _width + x] = round(colorCorrect(bufferColor * (255 / (power - 1))));
            }
        break;
    case Dithering::RANDOM:
        break;
    case Dithering::FLOYD_STEINBERG:
        break;
    case Dithering::JARVIS_JUDICE_NINKE:
        break;
    case Dithering::SIERRA:
        break;
    case Dithering::ATKINSOM:
        break;
    case Dithering::HALFTONE:
        break;
    default:
        break;
	}
}
