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


void toPGM(int rows, int cols, pVector** data, char* name, int flag = VALUE)
{
	int     i = 0, j = 0;
	string ft(".pgm");
	string h("_high"), l("_low");
	ofstream out;
	if(flag == LOW)
		out.open(name + l + ft, ios::out | ios::binary);
	else if (flag == HIGH)
		out.open(name + h + ft, ios::out | ios::binary);
	else 
		out.open(name + ft, ios::out | ios::binary);

	out << "P5\n";
	out << rows << " " << cols << "\n";
	out << rows << "\n";

	for (i = 0; i<rows; i++)
	{
		for (j = 0; j<cols; j++)
		{
			if (flag == 0)
				out << (char)data[i][j].value;
			if (flag == 1)
				out << (char)data[i][j].low;
			if (flag == 2)
				out << (char)data[i][j].high;

		}
	}
	out.close();
	return;
}


int main(int argc, char **argv)
{
	string foo;
	int i, j, p, q, mr, sum1, sum2, size = DIMENSIONS;
	double thresholdH, thresholdL;
	ifstream ip;
	ofstream op;
	char *fileName, *outName; // First Arg is File name. Second is output file, Third is threshold.
	

	argc--; argv++;
	fileName = *argv;
	ip.open(fileName, ios::in|ios::binary);
	
	argc--; argv++;
	outName = *argv;
	


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

	mr = 1;
	for (i = mr; i<256 - mr; i++)
	{
		for (j = mr; j<256 - mr; j++)
		{
			sum1 = 0;
			sum2 = 0;
			for (p = -mr; p <= mr; p++)
			{
				for (q = -mr; q <= mr; q++)
				{
					sum1 += pic[i + p][j + q].value * maskx[p + mr][q + mr];
					sum2 += pic[i + p][j + q].value * masky[p + mr][q + mr];
				}
			}
			outpicx[i][j] = sum1;
			outpicy[i][j] = sum2;
		}
	}

	maxival = 0;
	for (i = mr; i<256 - mr; i++)
	{
		for (j = mr; j<256 - mr; j++)
		{
			ival[i][j] = sqrt((double)((outpicx[i][j] * outpicx[i][j]) +
				(outpicy[i][j] * outpicy[i][j])));
			if (ival[i][j] > maxival)
				maxival = ival[i][j];

		}
	}



	for (i = 0; i<256; i++)
	{
		for (j = 0; j<256; j++)
		{
			pic[i][j].value = (ival[i][j] / maxival) * 255;
			if (pic[i][j].value > thresholdL)
			{
				pic[i][j].low = pic[i][j].value;
				if (pic[i][j].low > thresholdH)
					pic[i][j].high = pic[i][j].low;
			}

		}
	}

	toPGM(size, size, pic, outName, VALUE);
	toPGM(size, size, pic, outName, LOW);
	toPGM(size, size, pic, outName, HIGH);


	ip.close();
	op.close();
    return 0;
}

