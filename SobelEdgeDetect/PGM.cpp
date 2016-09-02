

#include "PGM.h"
#include <iostream>
#include <fstream>

PGM::PGM(int rows, int cols)
{
	int **image = (int**)calloc(cols, sizeof(int));
	for (int i = 0; i < cols; i++)
		image[i] = (int*)calloc(rows, sizeof(int));
}

void PGM::toPGM(int rows, int cols, pVector** data, ofstream out, int flag)
{
	int     i = 0, j = 0;

	out<< "P5\n";
	out << rows << " " << cols << "\n";
	out << rows << "\n";

	for (i = 0; i<rows; i++)
	{
		for (j = 0; j<cols; j++)
		{
			if(flag == 0)
				out<< (char)data[i][j].value;
			if (flag == 1)
				out << (char)data[i][j].peak;
			if (flag == 2)
				out << (char)data[i][j].lines;

		}
	}
	out.close();
	return;
}
