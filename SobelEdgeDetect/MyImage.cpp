
// By Adam Albright 
// Code available at https://github.com/Rehket/SobelEdgeDetect
// The image class containe the code for retrieveing the image, finding edges, and saving out the pgm.
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
	outX = (double **)calloc(_cols, sizeof(double));
	outY = (double **)calloc(_cols, sizeof(double));
	for (int i = 0; i < _cols; i++) {
		data[i] = (pVector*)calloc(_rows, sizeof(pVector));
		outX[i] = (double *)calloc(_rows, sizeof(double));
		outY[i] = (double *)calloc(_rows, sizeof(double));
	}
		
		
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

void MyImage::cannyEdge(float _threshold, int _rad, int _sigma, int _threshLow)
{	
	thresholdLow = _threshLow;
	int maskSize = (_rad * 2) + 1;
	int centX = maskSize / 2;
	int centY = maskSize / 2;
	


	double **maskX = NULL, ** maskY = NULL;

	gMask(maskX, maskY, _rad, _sigma, maskSize, centX, centY);


	cannyConvolution(data, maskX, maskY, _rad, centX, centY);
	cannyNormalize(outX, outY, data, _rad, _threshold);

	

	for (int i = 0; i < rowsX; i++)
	{
		for (int j = 0; j < colsY; j++)
		{
			if (data[i][j].norm > threshold)
				data[i][j].edge = data[i][j].norm;
		}
	}
	threshold = calcThreshold(_threshold);

	cannyEdgeCanditates(data, _rad);
	findLines(threshold);


	
	

}

void MyImage::cannyEdgeCanditates(pVector **&pic, int  _rad)
{
	for (int i = _rad; i < rowsX - _rad; i++)
	{
		for (int j = _rad; j < colsY - _rad; j++)
		{
			if ((pic[i][j].direction <= 22 && pic[i][j].direction > 337) || (pic[i][j].direction < 157 && pic[i][j].direction <= 202))
			{
				//Horizontal
				if ((pic[i][j].norm > pic[i][j - 1].norm) && (pic[i][j].norm > pic[i][j + 1].norm)) {
					pic[i][j].peak = 255;

				}
				else
					pic[i][j].peak = 0;

			}
			else if ((pic[i][j].direction <= 68 && pic[i][j].direction > 23) || (pic[i][j].direction < 203))
			{

				//Diagonal/

				if (pic[i][j].norm > pic[i - 1][j - 1].norm && pic[i][j].norm > pic[i + 1][j + 1].norm) {
					pic[i][j].peak = 255;

				}
				else
					pic[i][j].peak = 0;

			}
			else if ((pic[i][j].direction <= 157 && pic[i][j].direction > 113) || (pic[i][j].direction < 292))
			{

				//Diagonal\

				if (pic[i][j].norm > pic[i + 1][j - 1].norm && pic[i][j].norm > pic[i - 1][j + 1].norm) {
					pic[i][j].peak = 255;

				}
				else
					pic[i][j].peak = 0;

			}
			else {
				if (pic[i+1][j].norm > pic[i][j].norm && pic[i + 1][j].norm > pic[i][j].norm )
				{
					pic[i][j].peak = 255;

				}
				else
					pic[i][j].peak = 0;
			}
				
		}
	}
}


void MyImage::gMask(double  **&_maskX, double **&_maskY, int  _rad, int _sigma, int _size, int _centX, int _centY)
{
	double xVal = 0;
	double yVal = 0;

	_maskX = (double**)calloc(_size, sizeof(double));
	_maskY = (double**)calloc(_size, sizeof(double));
	for (int i = 0; i < _size; i++)
	{
		_maskX[i] = (double*)calloc(_size, sizeof(double));
		_maskY[i] = (double*)calloc(_size, sizeof(double));
	}



	for (int i = -_rad; i <= _rad; i++) {
		for (int j = -_rad; j <= _rad; j++) {
			xVal = i * (exp(-1 * (pow(i, 2) + pow(i, 2)) / (2 * pow(_sigma, 2))));
			yVal = j * (exp(-1 * (pow(j, 2) + pow(j, 2)) / (2 * pow(_sigma, 2))));
			_maskX[i + _centX][j + _centY] = xVal;
			_maskY[i +_centX][j + _centY] = yVal;
		}
	}

}

void MyImage::cannyConvolution( pVector **&pic, double ** _maskX, double ** _maskY, int _rad, int _centX, int _centY)
{ 
	double convX, convY;
	int dir = 0;

	for (int i = _rad; i < rowsX - _rad; i++) {
		for (int j = _rad; j < colsY - _rad; j++) {
			convX = convY = 0.0;
			for (int k = -_rad; k <= _rad; k++) {
				for (int l = -_rad; l <= _rad; l++) {
					convX += pic[i + k][j + l].value * _maskX[k + _centX][l + _centY];
					convY += pic[i + k][j + l].value * _maskY[k + _centX][l + _centY];
				}
			}

			dir = floor(atan2(convY, convX) / 3.14159265 * 180.0) + 360;
			pic[i - _rad][j - _rad].direction = dir % 360;

			outX[i][j] = convX;
			outY[i][j] = convY;
		}
	}
}



void MyImage::cannyNormalize(double ** _outX, double ** _outY, pVector **&_pic, int _rad, float _threshold)
{	
	
	double temp = 0;
	for (int i = _rad; i < rowsX - _rad; i++)
	{
		for (int j = _rad; j < colsY - _rad; j++)
		{
			temp = sqrt(pow(_outX[i][j], 2) + pow(_outY[i][j], 2));
			_pic[i][j].intensity = temp;
			
			if (temp < minIVal)
			{
				minIVal = temp;
			}
			else if (temp > maxIVal) {
				maxIVal = temp;
				//cout << maxIVal << "\n";
			}
		}
	}
	temp = 0;

	for (int i = 0; i < rowsX; i++)
	{
		for (int j = 0; j < colsY; j++) 
		{
			temp = _pic[i][j].intensity / maxIVal;
			_pic[i][j].norm = floor(temp * 255.0);
			histogram[_pic[i][j].norm]++;
		}
	}

}

void MyImage::findLines(float _threshold, int _sizeX, int _sizeY)
{
	for (int i = 1; i < _sizeX-1; i++) {
		for (int j = 1; j < _sizeY-1; j++) {
			if (data[i][j].peak == 255) {
				findNeighbors(_threshold*.5, i, j);
			}
		}
	}

}


void MyImage::findNeighbors(int _thresholdLow, int _x, int _y)
{
	//cout << "Low threshold is " << _thresholdLow <<". \n";
	if (data[_x][_y].edge < _thresholdLow || data[_x][_y].lines == 255)
	{ //Base Case
		return;
	}
		data[_x][_y].lines = 255;

		if ((data[_x][_y].direction <= 22 && data[_x][_y].direction > 337) || (data[_x][_y].direction < 157 && data[_x][_y].direction <= 202))
		{
			//Look Vertical
			if (data[_x][_y + 1].edge > data[_x][_y - 1].edge && data[_x][_y + 1].edge > _thresholdLow)
			{
				return findNeighbors(_thresholdLow, _x, _y + 1);
			}
			else if (data[_x][_y - 1].edge > _thresholdLow)
			{
				return findNeighbors(_thresholdLow, _x, _y - 1);
			}
		}

		else if ((data[_x][_y].direction <= 68 && data[_x][_y].direction > 23) || (data[_x][_y].direction < 203 && data[_x][_y].direction <= 248))
		{

			//Diagonal
			if (data[_x + 1][_y + 1].edge > data[_x - 1][_y - 1].edge && data[_x + 1][_y + 1].edge > _thresholdLow)
			{	
				return findNeighbors(_thresholdLow, _x + 1, _y - 1);
			}
			else if (data[_x - 1][_y - 1].edge > _thresholdLow)
			{
				return findNeighbors(_thresholdLow, _x - 1, _y - 1);
			}

		}
		else {
			//Horizontal
			if (data[_x + 1][_y].edge > data[_x][_y].edge && data[_x + 1][_y].edge > _thresholdLow)
			{	
				return findNeighbors(_thresholdLow, _x + 1, _y);
			}
			else if (data[_x + 1][_y].edge > _thresholdLow) {
				return findNeighbors(_thresholdLow, _x + 1, _y);
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
void MyImage::toPGM16(int _rows, int _cols, char* _fileName, string _threshold)
{
	int     i = 0, j = 0;

	string ft(".pgm");
	string it("_intensity");
	ofstream out;

	out.open(_fileName + it + ft, ios::out | ios::binary);

	//File header
	out << "P5\n";
	out << _rows << " " << _cols << "\n";
	out << maxIVal << "\n"; //Color range

	if (maxIVal < 255) {
		for (i = 0; i<_rows; i++)
		{
			for (j = 0; j<_cols; j++)
			{

				out << char (data[i][j].intensity);
			}
		}
		out.close();
		return;
	}

	for (i = 0; i<_rows; i++)
	{
		for (j = 0; j<_cols; j++)
		{

			out << unsigned short(data[i][j].intensity);
		}
	}
	out.close();
	return;
}

void MyImage::toPGM16(int _rows, int _cols, char * _name, double **arr)
{
	int     i = 0, j = 0;

	string ft(".pgm");

	ofstream out;

	out.open(_name + ft, ios::out | ios::binary);

	//File header
	out << "P5\n";
	out << _rows << " " << _cols << "\n";
	out << "65535" << "\n"; //Color range

	for (i = 0; i<_rows; i++)
	{
		for (j = 0; j<_cols; j++)
		{

			out << unsigned short(arr[i][j]);
		}
	}
	out.close();
	return;
}


//Saves the image as a PGM. Rows and cols are used to indicate the size of the image. The fileName parameter is what the file will be called.
//The flag is iused to indicate what pata is saved into the pgm. 
void MyImage::toPGM8(char* _fileName, string _threshold, int _flag, int _rows, int _cols)
{
	int     i = 0, j = 0;
	
	string ft(".pgm");
	string it("_intensity"), nom("_magnitude"), edge("_edge"), line("_final"), peak("_peak");
	ofstream out;
	
	if (_flag == EDGE)
		out.open(_fileName + edge + ft, ios::out | ios::binary);
	else if (_flag == NORM)
		out.open(_fileName + nom + ft, ios::out | ios::binary);
	else if (_flag == PEAK)
		out.open(_fileName + peak + ft, ios::out | ios::binary);
	else if (_flag == LINE)
		out.open(_fileName + line + ft, ios::out | ios::binary);
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
				if (_flag == EDGE)
					out << (char)data[i][j].edge;
				if (_flag == IN)
					out << (char)data[i][j].intensity;
				if (_flag == NORM)
					out << (char)data[i][j].norm;
				if (_flag == PEAK)
					out << (char)data[i][j].peak;
				if (_flag == LINE)
					out << (char)data[i][j].lines;
			}
		}
		out.close();
	return;
}


void MyImage::toPGM8(char* _fileName, unsigned int **_arr, int _rows, int _cols)
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
			out << int(data[i][j].direction);
			out << "\t";
		}
		out << "\n";
	}
	out.close();
}

void MyImage::toText(char *_fileName, double **_ar, int _sizeX, int _sizeY)
{
	int i = 0, j = 0;

	string txt(".txt");
	ofstream out;
	out.open(_fileName + txt, ios::out);

	for (i = 0; i < _sizeX; i++)
	{
		for (j = 0; j < _sizeY; j++)
		{
			out << (_ar[i][j]);
			out << " ";
		}
		out << "\n";
	}
	out.close();
}

int MyImage::calcThreshold(float _pcnt)
{	
	if (_pcnt > 1 || _pcnt < 0) 
	{
		cout << "ERROR: Threshold must be a percentage. \n";
			return 0;
	}
	int total = 0;
	for (int i = 0; i < 256; i++)
	{
		total += (histogram[i] * i);
	}
	cout << " Total is " << total << "\n";
	
	int target = total * _pcnt;
	
	cout << target << "\n";
	total = 0;

	for (int i = 255; i >= 0; i--) {
		total += histogram[i]*i;
		cout << " Total is " << total << "\t" << "Target is " << target <<".\n";
		if (total >= target)
		{	
			cout << "Break \n" << i;
			return (255 - i);

		}

	}

	return 0;
}
