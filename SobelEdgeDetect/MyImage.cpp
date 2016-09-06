

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
	double temp = 0.0, px = 0.0, py = 0.0;
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
			px = pow(outpicx[i][j], 2.0);
			py = pow(outpicy[i][j], 2.0);
			temp = sqrt(px+py);
			data[i][j].intensity = temp;
			
			if (data[i][j].intensity > maxIVal)
				maxIVal = int(data[i][j].intensity);
		}
		
	}

	cout << "\n" << maxIVal << "\n";
	cout << "\n";
	
	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{	
			temp = 0.0;
			temp = (data[i][j].intensity / maxIVal);

			data[i][j].norm = int(temp * 255.0);
			
			if (data[i][j].norm > threshold)
			{
				data[i][j].edge = data[i][j].norm;
			}

		}
	}
	toText("Edges");
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

			data[i][j].value = (unsigned char)temp;
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
	else if (flag == NORM)
		out.open(fileName + nom + ft, ios::out | ios::binary);
	else
		out.open(fileName + ft, ios::out | ios::binary);

	out << "P5\n";
	out << rows << " " << cols << "\n";
	out << "255" << "\n";

		for (i = 0; i<rows; i++)
		{
			for (j = 0; j<cols; j++)
			{
				if (flag == 0)
					out << (char)data[i][j].value;
				if (flag == 1 || flag == 2)
					out << (char)data[i][j].edge;
				if (flag == IN)
					out << (char)data[i][j].intensity;
				if (flag == NORM)
					out << (char)data[i][j].norm;
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
				out << arr[i][j];

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
			out << int(data[i][j].intensity);
			out << " ";
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
