

#include "PGM.h"
#include <iostream>
#include <fstream>

//Builds a PGM Object
PGM::PGM(int rows, int cols)
{
	rowsX = rows;
	colsY = cols;
	data = (pVector**)calloc(cols, sizeof(pVector));
	for (int i = 0; i < cols; i++)
		data[i] = (pVector*)calloc(rows, sizeof(pVector));
		
}

PGM::~PGM() {}


void PGM::fillData(char *fileName, int size)
{	
	char temp;
	ifstream ip;
	ip.open(fileName, ios::in | ios::binary);

	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
		{
			ip.read(&temp, sizeof(temp));

			//pic[i][j].value &= 0377;
			data[i][j].value = (unsigned char)temp;
		}
	}
	ip.close();
}

void PGM::toPGM(int rows, int cols, char* fileName, int flag)
{
	int     i = 0, j = 0;
	
	string ft(".pgm");
	string h("_high"), l("_low"), it("_intensity"), nom("_normalized");
	ofstream out;
	if (flag == LOW)
		out.open(fileName + l + ft, ios::out | ios::binary);
	else if (flag == HIGH)
		out.open(fileName + h + ft, ios::out | ios::binary);
	else if (flag == IN)
		out.open(fileName + it + ft, ios::out | ios::binary);
	else if (flag == NORM)
		out.open(fileName + nom + ft, ios::out | ios::binary);
	else
		out.open(fileName + ft, ios::out | ios::binary);

	out << "P5\n";
	out << rowsX << " " << colsY << "\n";
	out << "255" << "\n";

		for (i = 0; i<rowsX; i++)
		{
			for (j = 0; j<colsY; j++)
			{
				if (flag == 0)
					out << (char)data[i][j].value;
				if (flag == 1)
					out << (char)data[i][j].low;
				if (flag == 2)
					out << (char)data[i][j].high;
				if (flag == IN)
					out << (char)data[i][j].intensity;
				if (flag == NORM)
					out << (char)data[i][j].normalized;

			}
		}
		out.close();
	return;
}

void PGM::toText(char * fileName)
{
	int i = 0, j = 0;

	string txt(".txt");
	ofstream out;
	out.open(fileName + txt, ios::out);

	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{
			out << data[i][j].value;
			out << " ";
		}
		out << "\n";
	}
	out.close();
}
