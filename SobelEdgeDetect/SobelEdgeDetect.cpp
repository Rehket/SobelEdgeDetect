/* SobelEdgeDetect.cpp : This program implements a sobel edge detect program. The Sobel code is modified from http://www.cs.ucf.edu/courses/cap4453/progs/sobel.c
	by Adam Albright for CAP 4453 Robot Vision
*/

#include "stdafx.h"
#include "PGM.h"

using namespace std;

const int DIMENSIONS = 256;
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
int masky[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
double ival[256][256], maxival;

pVector **pic;	//The pointer to our image.

int main(int argc, char **argv)
{
	string foo;
	int i, j, p, q, mr, sum1, sum2, size = DIMENSIONS;
	double thresholdH, thresholdL;
	ifstream ip;
	ofstream op;
	char *fileName; // First Arg is File name. Second is output file, Third is threshold.

	argc--; argv++;
	fileName = *argv;
	ip.open(fileName, ios::in|ios::binary);
	
	argc--; argv++;
	fileName = *argv;
	op.open(fileName, ios::out|ios::binary); //Output File


	argc--; argv++;
	fileName = *argv;
	thresholdH = atof(fileName); //Threshold

	argc--; argv++;
	fileName = *argv;
	thresholdL = atof(fileName); //Threshold

	pic = (pVector**)calloc(size, sizeof(pVector));

	for (i = 0; i < size; i++)
	{
		pic[i] = (pVector*)calloc(size, sizeof(pVector));
	}

	char temp;
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			ip.read(&temp, sizeof(char));
			pic[i][j].value = (int)temp;
			pic[i][j].value &= 0377;
		}
	}

	//For Debugging.
	/*for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			
			op << pic[i][j].value << " ";
		}
		op << "\n";
	}
	*/





	ip.close();
	op.close();
    return 0;
}

