#include "Dithering.h"

using namespace std;

int main(int argc, char** argv)
{
	//lab4.exe file.pnm newFile.pnm grad dith bit gamma
	// ff
	if (argc == 7)
	{
		Dithering image;

		image.readFile(argv[1]);

		image.setGamma(atof(argv[6]));
		image.setBit(atoi(argv[5]));

		if (atoi(argv[3]) == 1)
			image.drawGradient();
		image.dithering((Dithering::DITHERING_TYPE)atoi(argv[4]));
		
		image.writeFile(argv[2]);
	}
	else
	{
		cerr << "Incorrect arguments" << endl;
		return 1;
	}

	return 0;
}