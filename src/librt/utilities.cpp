//----------------------------------------
// Copyright 2015 Corey Toler-Franklin,
// University of Florida
// utility functions
// utilities.cpp
//----------------------------------------

#include "utilities.h"
#include <limits>
#include "STVector3.h"
#include <cmath>

//------------------------------------
// conversions
//------------------------------------

// converts a unsigned char to a float
float UcharToFloat(unsigned char c)
{
    return(c/255.0f);
}


// converts a float to unsigned char
unsigned char floatToUchar (float f)
{
    return((unsigned char)(f * 255));
}

double findTriangleArea (STVector3 A, STVector3 B, STVector3 C)
{
	// We use Herons formula here to determine the area of a triangle given it's three points

	STVector3 AB = A - B;
	STVector3 BC = B - C;
	STVector3 CA = C - A;

	double ABLength = AB.Length();
    double BCLength = BC.Length();
    double CALength = CA.Length();

    double S = (ABLength + BCLength + CALength) / 2.0;

    return sqrt(S * (S - ABLength) * (S - BCLength) * (S - CALength));
}