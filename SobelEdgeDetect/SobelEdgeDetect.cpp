// SobelEdgeDetect.cpp : This program implements a sobel edge detect program. The Sobel code is provided by 
//

#include "stdafx.h"
#include <math.h>

int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
int masky[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
double ival[256][256], maxival;

int main(int argc, char **argv)
{
	int i, j, p, q, mr, sum1, sum2;
	double threshold;
	FILE *fo1, *fo2, *fp1, *fopen(const char * filename, const char * mode);
	char *fileName; // First Arg is File name. Second is output file, Third is threshold.

	argc--; argv++;
	fileName = *argv;
	fp1 = fopen(fileName, "rb"); //Input File

	argc--; argv++;
	fileName = *argv;
	fo1 = fopen(fileName, "wb"); //Output File


	argc--; argv++;
	fileName = *argv;
	threshold = atof(fileName); //Threshold

    return 0;
}

