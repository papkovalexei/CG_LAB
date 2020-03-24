#include <cmath>

#include "Instruments.h"

int main(int argc, char** argv)
{
	// lab3.exe file.pnm newFile.pnm brit width x0 y0 x1 y1 gamma

	if (argc < 8)
		cerr << "Error input data" << endl;
	else
	{
		Instruments instrument;

		if (argc == 10)
			instrument.setGamma(atof(argv[9]));
		

		instrument.readFile(argv[1]);

		instrument.drawLine(atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[4]), atof(argv[3]));

		instrument.writeFile(argv[2]);
	}

	return 0;
}