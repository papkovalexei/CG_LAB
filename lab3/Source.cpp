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
		
		instrument.readFile(argv[1]);

		instrument.drawLine(Vertex(atof(argv[5]), atof(argv[6])), Vertex(atof(argv[7]), atof(argv[8])), atof(argv[4]), atof(argv[3]));

		instrument.writeFile(argv[2]);
	}

	return 0;
}