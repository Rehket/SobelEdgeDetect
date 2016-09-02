#pragma once
/*PGM.h: Header file for PGM.cpp
TODO: PGM to RAW
TODO: RAW to PGM
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>

class PGM
{
public:
	 PGM(int rows, int cols);
	~PGM();

	int rows, cols, maxVal;

	//Converts RAW image data to PGM, The flag indicates what part of the data we are interested in printing.

	void PGM::toPGM(int rows, int cols, pVector** data, ofstream out, int flag = VALUE);

	//Converts PGM image data to RAW
	void toRAW(char *filename);

};

