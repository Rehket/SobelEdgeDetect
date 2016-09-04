/* main.cpp : This program implements a sobel edge detection algorithim. 
	Adam Albright
	aalbright425@gmail.com
*/

#include "stdafx.h"
#include "MyImage.h"

using namespace std;

const int DIMENSIONS = 256;
int maskx[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
int masky[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };



//pVector **pic;	//The pointer to our image.



int main(int argc, char **argv)
{
	string foo;
	int i, j, p, q, mr, sum1, sum2, size = DIMENSIONS;
	double thresholdH, thresholdL;
	
	ofstream op;
	char *thresh, *outName, *inName; // First Arg is File name. Second is output file, Third is threshold.
	
	//The input file fame
	argc--; argv++;
	inName = *argv;
	
	//The Output file name
	argc--; argv++;
	outName = *argv;
	cout << outName;


	argc--; argv++;
	thresh = *argv;
	thresholdH = atof(thresh); //Threshold

	argc--; argv++;
	thresh = *argv;
	thresholdL = atof(thresh); //Threshold

	//pic = (pVector**)calloc(size, sizeof(pVector));
	MyImage pic = MyImage::MyImage(size, size);
	pic.fillData(inName, size);

	pic.toPGM(size, size, "Input File", VALUE);

	pic.sobelEdge(10, NULL, NULL, 1);

	/*pic.toPGM(size, size, outName, VALUE);

	pic.toPGM(size, size, outName, NORM);

	
	pic.toPGM(size, size, outName, LOW);

	pic.sobelEdge(thresholdH, NULL, NULL, 1);
	pic.toPGM(size, size, outName, HIGH);
	*/
	cin >> string();

	


	op.close();
    return 0;
}

