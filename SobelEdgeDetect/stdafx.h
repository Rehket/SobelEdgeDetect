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

//Will be used to store the image found with different thresholds.
typedef struct {
	double mag;	//Normalized Vector length
	int value;	//vector Length
	int high;
	int low;		
}pVector;

enum DataFlags
{
	VALUE = 0, LOW, HIGH
};



// TODO: reference additional headers your program requires here
