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
	int peak;
	int direction;
	int edge;
	int lines;
	double intensity;
}pVector;

//Enum Used to 
enum DataFlags
{
	VALUE = 0, EDGE, TEXT, IN, NORM, PEAK, LINE
};



class MyImage
{
public:
	//The image Data
	pVector **data;
	int maxIVal = 0, minIVal = 0;
	int **outPicX;
	int **outPicY;
	int outpicx[256][256];
	int outpicy[256][256];
	double **outX, **outY;
	int histogram[256] = { 0 };
	int threshold = 100;
	int thresholdLow = 35;
	MyImage(const int rows, const int cols);
	~MyImage();

	//Looks for edges using the sobel edge detection algorithim located at http://www.cs.ucf.edu/courses/cap4453/progs/sobel.c
	//The image data is the edge variable of the data matrix.
	void sobelEdge(int _threshold = 0, int **_xM = NULL, int **_yM = NULL, int _maskRad = 1);
	
	// Looks for edges using the Canny edge detection method.
	void cannyEdge(float _threshold, int _rad = 1, int _sigma = 1, int _threshLow = 35.0);

	// Edge detection through the canny algorithim.
	void cannyEdgeCanditates(pVector **&pic, int  _rad);

	//Builds a gaussian mask
	void gMask(double **&_maskX, double **&_maskY, int _rad, int _sigma, int _size, int _centX, int _centY);

	//Convolution for the canny edge detection
	void cannyConvolution(pVector **&pic, double **_maskX, double **_maskY, int _rad, int _centX, int _centY);

	// Calculates the Intensity and normalizes the image.
	void cannyNormalize(double **outX, double **outY, pVector **&pic, int _rad, float _thresh = .35f);

	void findLines(float _threshold, int _sizeX = 256, int _sizeY = 256);

	// Find Neighbor pixels that are part of the edge.
	void findNeighbors(int _thresholdLow, int _x, int _y);

	//Reads the Raw Image data from the file in the program directory.
	void fillPGM(char *_fileName, int _size);

	//Converts image data to PGM 8-bit, The flag indicates what part of the data we are interested in printing.
	void toPGM8(char* _name, string _threshold, int _flag = VALUE, int _rows = 256, int _cols = 256);

	//Converts image data to PGM 16-bit, The flag indicates what part of the data we are interested in printing.
	void toPGM16(int _rows, int _cols, char* _name, string _threshold);

	//Converts image data to PGM 16-bit, The flag indicates what part of the data we are interested in printing.
	void toPGM16(int _rows, int _cols, char* _name, double **data);

	//Array to PGM
	void toPGM8(char* _fileName, unsigned int **_arr, int _rows = 256, int _cols = 256);

	//Converts PGM image data to 8-Bit Binary data.
	void toBin8(char *_filename);

	//Prints the PGM to file in plain text. The parameter is the desired name for the file.
	void toText(char *_fileName);

	void toText(char *_fileName, double **_ar, int _sizeX = 256, int _sizeY = 256);

	//This function uses the histogram built during normalization to find a percentage threshold.
	int calcThreshold(float _pcnt);

private:
	int rowsX = 0, colsY = 0;
	

};

