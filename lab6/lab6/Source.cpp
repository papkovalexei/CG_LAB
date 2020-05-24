#include <iostream>

#include "Image.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cerr << "Incorrect arguments" << endl;
		return 1;
	}

	string input_file = argv[1];
	string output_file = argv[2];
	float offset, multi;
	Image image;

	if (atoi(argv[3]) > 6)
	{
		cerr << "Incorrect convertation" << endl;
		return 1;
	}

	Brit current = static_cast<Brit>(atoi(argv[3]));

	if (current == RGB || current == YCBCR)
	{
		offset = atoi(argv[4]);
		multi = atof(argv[5]);
	}

	if (current == YCBCR || current == YCBCR_AUTO || current == YCBCR_AUTO_PLUS)
		image.setColorSpace(YCBCR_CS);
	else
		image.setColorSpace(RGB_CS);

	image.readFile(input_file);

	if (current == RGB || current == YCBCR)
		image.changeBrit(offset, multi);
	else
	{
		if (current == RGB_AUTO || current == YCBCR_AUTO)

	}

	return 0;
}