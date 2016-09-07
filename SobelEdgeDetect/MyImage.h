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
	VALUE = 0, EDGE, TEXT, IN, NORM
};



class MyImage
{
public:
	//The image Data
	pVector **data;
	int maxIVal = 0;
	int **outPicX;
	int **outPicY;
	int outpicx[256][256];
	int outpicy[256][256];
	MyImage(const int rows, const int cols);
	~MyImage();

	//Looks for edges using the sobel edge detection algorithim located at http://www.cs.ucf.edu/courses/cap4453/progs/sobel.c
	//The image data is the edge variable of the data matrix.
	void sobelEdge(int _threshold = 0, int **_xM = NULL, int **_yM = NULL, int _maskRad = 1);

	//Reads the Raw Image data from the file in the program directory.
	void fillPGM(char *_fileName, int _size);

	//Converts image data to PGM, The flag indicates what part of the data we are interested in printing.
	void toPGM(int _rows, int _cols, char* _name, string _threshold, int _flag = VALUE);

	//Array to PGM
	void toPGM(int _rows, int _cols, char* _fileName, unsigned int **_arr);

	//Converts PGM image data to 8-Bit Binary data.
	void toBin8(char *_filename);

	//Prints the PGM to file in plain text. The parameter is the desired name for the file.
	void toText(char *_fileName);

	void toText(char * _fileName, unsigned int** _ar);

private:
	int rowsX, colsY;
	

};

