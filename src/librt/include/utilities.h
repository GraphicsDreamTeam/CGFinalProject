//----------------------------------------
// Copyright 2015 Corey Toler-Franklin,
// University of Florida
// utility functions
// utilities.h
//----------------------------------------

#include "STVector3.h"

#ifndef __UTILITIES_H__
#define __UTILITIES_H__


// conversions
float               UcharToFloat                (unsigned char c);
unsigned char       floatToUchar                (float f);
double 				findTriangleArea			(STVector3 A, STVector3 B, STVector3 c);

#endif //__UTILITIES_H__

