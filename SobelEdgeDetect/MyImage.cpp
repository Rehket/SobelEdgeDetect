

#include "MyImage.h"
#include <iostream>
#include <fstream>


//Builds a Image Object
MyImage::MyImage(int _rows, int _cols)
{
	rowsX = _rows;
	colsY = _cols;
	//data = new pVector *[rowsX]; //C++ method for memory allocation. Needs to be fixed.
	//for (int i = 0; i < _cols; i++) data[i] = new pVector[colsY];
	data = (pVector**)calloc(_cols, sizeof(pVector));
	for (int i = 0; i < _cols; i++)
		data[i] = (pVector*)calloc(_rows, sizeof(pVector));
		
}

//Default Destructor
MyImage::~MyImage() {}


/*Edge detection using the Sobel algorithim. 
*/
void MyImage::sobelEdge(int _threshold, int **_xM, int **_yM, int _maskRad)
{
	//default mask and mask radius for the sobel algorithm.
	int defaultMaskX[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
	int defaultMaskY[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
	int dMaskRadius = 1;
	int i = 0, j = 0, p = 0, q = 0;
	int sum1 = 0, sum2 = 0;
	double temp = 0.0, px = 0.0, py = 0.0;
	maxIVal = 0;
	


	//The image is convolved with a 3x3 x and y mask. 
	for (i = _maskRad; i < rowsX - _maskRad; i++)
	{
		for (j = _maskRad; j < colsY - _maskRad; j++)
		{
			sum1 = 0;
			sum2 = 0;
			for (p = -_maskRad; p <= _maskRad; p++)
			{
				for (q = -_maskRad; q <= _maskRad; q++)
				{
					sum1 += data[i + p][j + q].value * defaultMaskX[p + _maskRad][q + _maskRad];	
					sum2 += data[i + p][j + q].value * defaultMaskY[p + _maskRad][q + _maskRad];
				}
			}
			outpicx[i][j] = sum1;
			outpicy[i][j] = sum2;
		}
	}

	//The results of the X and Y convolution is calculated by using the distance formula where the value of each cell in 
	// the convolution masks is combined to get the intensity matrix.
	for (i = _maskRad; i < rowsX - _maskRad; i++)
	{
		for (j = _maskRad; j < colsY - _maskRad; j++)
		{
			px = pow(outpicx[i][j], 2.0);
			py = pow(outpicy[i][j], 2.0);
			temp = sqrt(px+py);
			data[i][j].intensity = temp;
			
			if (data[i][j].intensity > maxIVal)
				maxIVal = int(data[i][j].intensity);
		}
		
	}
	
	//The values of the intensity matrix are normallized to between 0 and 255 before being compared to threshold. If the normalized value 
	//exceeds the threshold, the value will be stored into the edge matix.
	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{	
			temp = 0.0;
			temp = (data[i][j].intensity / maxIVal);
			data[i][j].norm = int(temp * 255.0);
			
			if (data[i][j].norm > _threshold)
			{
				data[i][j].edge = data[i][j].norm;
			}
		}
	}
}

//fillData gets the PGN image data from the specified file. The image needs to have equal width and height.
void MyImage::fillPGM(char *_fileName, int _size)
{	
	char temp;
	ifstream ip;
	ip.open(_fileName, ios::in | ios::binary);

	for (int i = 0; i<_size; i++)
	{
		for (int j = 0; j<_size; j++)
		{
			ip.read(&temp, sizeof(temp));

			data[i][j].value = (unsigned char)temp;
		}
	}
	ip.close();
}


//Saves the image as a PGM. Rows and cols are used to indicate the size of the image. The fileName parameter is what the file will be called.
//The flag is iused to indicate what pata is saved into the pgm. 
void MyImage::toPGM(int _rows, int _cols, char* _fileName, string _threshold, int _flag)
{
	int     i = 0, j = 0;
	
	string ft(".pgm");
	string it("_intensity"), nom("_normalized");
	ofstream out;
	
	if (_flag == EDGE)
		out.open(_fileName + _threshold + ft, ios::out | ios::binary);
	else if (_flag == NORM)
		out.open(_fileName + nom + ft, ios::out | ios::binary);
	else
		out.open(_fileName + ft, ios::out | ios::binary);

	//File header
	out << "P5\n";
	out << _rows << " " << _cols << "\n";
	out << "255" << "\n"; //Color range

		for (i = 0; i<_rows; i++)
		{
			for (j = 0; j<_cols; j++)
			{
				if (_flag == 0)
					out << (char)data[i][j].value;
				if (_flag == 1 )
					out << (char)data[i][j].edge;
				if (_flag == IN)
					out << (char)data[i][j].intensity;
				if (_flag == NORM)
					out << (char)data[i][j].norm;
			}
		}
		out.close();
	return;
}

void MyImage::toPGM(int _rows, int _cols, char* _fileName, unsigned int **_arr)
{
	int     i = 0, j = 0;

	string ft("_debug.pgm");

	ofstream out;
		out.open(_fileName + ft, ios::out | ios::binary);

	out << "P5\n";
	out << _rows << " " << _cols << "\n";
	out << "255" << "\n";

	for (i = 0; i<_rows; i++)
	{
		for (j = 0; j<_cols; j++)
		{
				out << _arr[i][j];
		}
	}
	out.close();
	return;
}

void MyImage::toText(char *_fileName)
{
	int i = 0, j = 0;

	string txt(".txt");
	ofstream out;
	out.open(_fileName + txt, ios::out);

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

void MyImage::toText(char *_fileName, unsigned int **_ar)
{
	int i = 0, j = 0;

	string txt(".txt");
	ofstream out;
	out.open(_fileName + txt, ios::out);

	for (i = 0; i < rowsX; i++)
	{
		for (j = 0; j < colsY; j++)
		{
			out << _ar[i][j];
			out << " ";
		}
		out << "\n";
	}
	out.close();
}
