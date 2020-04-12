#include "Dithering.h"

using namespace std;

int main(int argc, char** argv)
{
	//lab4.exe file.pnm newFile.pnm grad dith bit gamma

	if (argc == 7)
	{
		Dithering image;

		image.readFile(argv[1]);

		image.setGamma(atof(argv[6]));
		image.setBit(atoi(argv[5]));

		if (atoi(argv[3]) == 1)
			image.drawGradient();

		image.dithering(Dithering::HALFTONE);

		image.writeFile(argv[2]);
	}

	return 0;
}