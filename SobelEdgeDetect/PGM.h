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
	int low;	//Value of pixel after being tested at the low threshold.
	int high;	//Value of pixel after being tested at the high threshold.
	int normalized;
	double intensity;
}pVector;

//Enum Used to 
enum DataFlags
{
	VALUE = 0, LOW, HIGH, TEXT, IN, NORM
};

class PGM
{
public:
	//The image Data
	pVector **data;

	int maxIVal = 0;

	 PGM(int rows, int cols);
	~PGM();

	//Reads the Raw Image data from the file in the program directory.
	void fillData(char *fileName, int size);

	//Converts image data to PGM, The flag indicates what part of the data we are interested in printing.
	void toPGM(int rows, int cols, char* name, int flag = VALUE);

	//Converts PGM image data to RAW
	void toRAW(char *filename);

	//Prints the PGM to file in plain text.
	void toText(char *fileName);



private:
	int rowsX, colsY;
	

};

