#pragma once
/*PGM.h: Header file for PGM.cpp
TODO: PGM to RAW
TODO: RAW to PGM
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>


//Will be used to store the image found with different thresholds.
typedef struct {
	int value;	//vector Length
	int norm;	//Value of pixel after being tested at the low threshold.
	//unsigned int high;	//Value of pixel after being tested at the high threshold.
	int edge;
	double intensity;
}pVector;

//Enum Used to 
enum DataFlags
{
	VALUE = 0, LOW, HIGH, TEXT, IN, NORM
};

static unsigned int defaultMaskX[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
static unsigned int defaultMaskY[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };



class MyImage
{
public:
	//The image Data
	pVector **data;

	double maxIVal = 0;
	int **outPicX;
	int **outPicY;
	int dMaskRadius = 1;
	int outpicx[256][256];
	int outpicy[256][256];
	MyImage(int rows, int cols);
	~MyImage();

	//Looks for edges using the sobel edge detection algorithim located at http://www.cs.ucf.edu/courses/cap4453/progs/sobel.c
	//The image data is the edge variable of the data matrix.
	void sobelEdge(int threshold = 0, int **xM = NULL, int **yM = NULL, int maskRad = 1);

	//Reads the Raw Image data from the file in the program directory.
	void fillData(char *fileName, int size);

	//Converts image data to PGM, The flag indicates what part of the data we are interested in printing.
	void toPGM(int rows, int cols, char* name, int flag = VALUE);

	//Array to PGM
	void toPGM(int rows, int cols, char* fileName, unsigned int **arr);

	//Converts PGM image data to 8-Bit Binary data.
	void toBin8(char *filename);

	//Prints the PGM to file in plain text. The parameter is the desired name for the file.
	void toText(char *fileName);

	void toText(char * fileName, unsigned int** ar);

private:
	int rowsX, colsY;
	

};

