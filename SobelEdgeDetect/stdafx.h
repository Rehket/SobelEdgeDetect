// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Will be used to store the direction of the gradient and the value for the pixel.
typedef struct {
	double mag;	//Normalized Vector length
	int value;	//vector Length
	int direction;//The direction of the vector
	int peak;		//The prospective edges
	int lines;	//The final image after all excess lines have beed removed.
}pVector;

enum DataFlags
{
	VALUE = 0, PEAKS, LINES
};



// TODO: reference additional headers your program requires here
