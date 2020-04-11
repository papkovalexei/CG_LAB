#include "Dithering.h"



void Dithering::dithering(DITHERING_TYPE type)
{
	switch (type)
	{
    case Dithering::NONE:
        break;
    case Dithering::ORDERED:
        uchar* buffer = (uchar*)malloc(_width * _height * sizeof(uchar));

        for (int y = 0; y < _height; y++)
            for (int x = 0; x < _width; x++)
            {

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
