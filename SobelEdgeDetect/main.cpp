/* main.cpp : This program implements a sobel edge detection algorithim. 
	Adam Albright
	aalbright425@gmail.com
*/

#include "stdafx.h"
#include "MyImage.h"

using namespace std;

const int DIMENSIONS = 256;

//pVector **pic;	//The pointer to our image.

int main(int argc, char **argv)
{
	int i, j, p, q, mr, sum1, sum2, size = DIMENSIONS, option = 0;

	
	ofstream op;
	char *thresh, *outName, *inName; // First Arg is File name. Second is output file, Third is threshold.
	
	//Sobel or Canny
	argc--; argv++;
	option = atoi(*argv);



/*		//The input file fame
		argc--; argv++;
		inName = *argv;

		//The Output file name
		argc--; argv++;
		outName = *argv;

		MyImage pic = MyImage::MyImage(size, size);
		pic.fillPGM(inName, size);
		pic.toPGM8(size, size, outName, "0", 1);
		argc--; argv++;
		while (argc > 0)
		{
			thresh = *argv;
			threshold = atof(thresh);
			pic.sobelEdge(threshold, NULL, NULL, 1);
			pic.toPGM8(size, size, outName, thresh, EDGE);
			argc--; argv++;
		}
	}
	*/

		//The input file fame
		argc--; argv++;
		inName = *argv;

		//The Output file name
		argc--; argv++;
		outName = *argv;

		MyImage pic = MyImage::MyImage(size, size);
		pic.fillPGM(inName, size);
		pic.toPGM8(outName, "0", 0);
		pic.cannyEdge( .50 , 1, 1);
		pic.toPGM8(outName, "100", NORM);
		pic.toPGM8(outName, " 150", PEAK);
		pic.toPGM8(outName, " 150", EDGE);
		pic.toPGM8(outName, " 150", LINE);
		//pic.toPGM8(outName, to_string(pic.threshold), LINE);
	
		//cout << "Parameter not recogognized.\n Expects 0 or 1 for sobel or Canny edge dectection respectivly.";
	


	cin.get();


	//pic = (pVector**)calloc(size, sizeof(pVector));
	

	//pic.toPGM(size, size, "Input File", VALUE);

	
	//pic.sobelEdge(thresholdL, NULL, NULL, 1);
	//pic.toPGM(size, size, outName, LOW);

	op.close();
    return 0;
}

