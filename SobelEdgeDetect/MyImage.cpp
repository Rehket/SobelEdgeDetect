

#include "MyImage.h"
#include <iostream>
#include <fstream>

//Builds a Image Object
MyImage::MyImage(int rows, int cols)
{
	rowsX = rows;
	colsY = cols;
	data = (pVector**)calloc(cols, sizeof(pVector));
	for (int i = 0; i < cols; i++)
		data[i] = (pVector*)calloc(rows, sizeof(pVector));
		
}

//Default Destructor
MyImage::~MyImage() {}

void MyImage::sobelEdge(int threshold, int **xM, int **yM, int maskRad)
{
	int i = 0, j = 0, p = 0, q = 0;
	int sum1 = 0, sum2 = 0;

	maxIVal = 0;




	for (i = maskRad; i < rowsX - maskRad; i++)
	{
		for (j = maskRad; j < colsY - maskRad; j++)
		{
			sum1 = 0;
			sum2 = 0;
			for (p = -maskRad; p <= maskRad; p++)
			{
				for (q = -maskRad; q <= maskRad; q++)
				{
					sum1 += data[i + p][j + q].value * defaultMaskX[p + maskRad][q + maskRad];
					
					sum2 += data[i + p][j + q].value * defaultMaskY[p + maskRad][q + maskRad];
				}
			}
			outpicx[i][j] = sum1;
			outpicy[i][j] = sum2;
		}
	}

	for (i = maskRad; i < rowsX - maskRad; i++)
	{
		for (j = maskRad; j < colsY - maskRad; j++)
		{
			data[i][j].intensity = sqrt(pow(outpicx[i][j], 2) * pow(outpicy[i][j], 2));
			//cout << data[i][j].intensity;
			//cout << "\t";
			if (data[i][j].intensity > maxIVal)
				maxIVal = data[i][j].intensity;

		}
		
	}

	cout << maxIVal;
	cout << "\n";

	toPGM(rowsX, colsY, "out", IN);
	
	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{
			data[i][j].norm = (data[i][j].intensity / maxIVal) * 255;
			//cout << (data[i][j].intensity / maxIVal);
			//cout << "\n";
			if (data[i][j].norm > threshold)
			{
				data[i][j].edge = data[i][j].norm;
			}

		}
	}
	toText("debug Norm");

	toPGM(rowsX, colsY, "Normal", NORM);
	toPGM(rowsX, colsY, "Edges", HIGH);
}

void MyImage::fillData(char *fileName, int size)
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
			data[i][j].value = temp;
		}
	}
	ip.close();
}

void MyImage::toPGM(int rows, int cols, char* fileName, int flag)
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
					out << char(data[i][j].value);
				if (flag == IN)
					out << char(data[i][j].intensity);
				if (flag == NORM)
					out << unsigned char(data[i][j].norm);
				if(flag == LOW || flag == HIGH)
					out << unsigned char(data[i][j].edge);

			}
		}
		out.close();
	return;
}

void MyImage::toPGM(int rows, int cols, char* fileName, unsigned int **arr)
{
	int     i = 0, j = 0;

	string ft("_debug.pgm");

	ofstream out;
		out.open(fileName + ft, ios::out | ios::binary);

	out << "P5\n";
	out << rows << " " << cols << "\n";
	out << "255" << "\n";

	for (i = 0; i<rows; i++)
	{
		for (j = 0; j<cols; j++)
		{
				out << (char)arr[i][j];

		}
	}
	out.close();
	return;
}

void MyImage::toText(char * fileName)
{
	int i = 0, j = 0;

	string txt(".txt");
	ofstream out;
	out.open(fileName + txt, ios::out);

	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{
			out << to_string(data[i][j].norm);
			out << "\t";
		}
		out << "\n";
	}
	out.close();
}

void MyImage::toText(char * fileName, unsigned int** ar)
{
	int i = 0, j = 0;

	string txt(".txt");
	ofstream out;
	out.open(fileName + txt, ios::out);

	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{
			out << ar[i][j];
			out << " ";
		}
		out << "\n";
	}
	out.close();
}
