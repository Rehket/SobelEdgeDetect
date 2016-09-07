/* main.cpp : This program implements a sobel edge detection algorithim. 
	Adam Albright
	aalbright425@gmail.com
*/

#include "stdafx.h"
#include "MyImage.h"

using namespace std;

const int DIMENSIONS = 256;
//int maskx[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
//int masky[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };



//pVector **pic;	//The pointer to our image.



int main(int argc, char **argv)
{
	string foo;
	int i, j, p, q, mr, sum1, sum2, size = DIMENSIONS;
	double threshold;
	
	ofstream op;
	char *thresh, *outName, *inName; // First Arg is File name. Second is output file, Third is threshold.
	
	//The input file fame
	argc--; argv++;
	inName = *argv;
	
	//The Output file name
	argc--; argv++;
	outName = *argv;

	MyImage pic = MyImage::MyImage(size, size);
	pic.fillPGM(inName, size);
	argc--; argv++;
	while (argc > 0) 
	{
		thresh = *argv;
		threshold = atof(thresh);
		pic.sobelEdge(threshold, NULL, NULL, 1);
		pic.toPGM(size, size, outName, thresh, EDGE);
		argc--; argv++;
	}




	//pic = (pVector**)calloc(size, sizeof(pVector));
	

	//pic.toPGM(size, size, "Input File", VALUE);

	
	//pic.sobelEdge(thresholdL, NULL, NULL, 1);
	//pic.toPGM(size, size, outName, LOW);


	op.close();
    return 0;
}

