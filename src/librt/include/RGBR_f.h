//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// RGBR_f.h
// Color data
//------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <algorithm>


#ifndef _RGBR_F_H
#define _RGBR_F_H


class RGBR_f {

public:

    RGBR_f(void);
    RGBR_f(float red, float green, float blue, float alpha);
    ~RGBR_f(void);

    inline static RGBR_f Min(const RGBR_f& left, const RGBR_f& right) {
        return RGBR_f(std::min(left.r, right.r), std::min(left.g, right.g), std::min(left.b, right.b), 255);
    }

    inline static RGBR_f Average(const RGBR_f& left, const RGBR_f& right)
	{
	    return RGBR_f((left.r + right.r) / 2, (left.g + right.g) / 2, (left.b + right.b) / 2, (left.a + right.a) / 2);
	}

    inline static RGBR_f Multiply(const RGBR_f& left, const RGBR_f& right) {
        return RGBR_f(left.r * right.r / 255, left.g * right.g / 255, left.b * right.b / 255, 255);
    }

	// inline static RGBR_f Average(const RGBR_f& left, const RGBR_f& right);

    inline RGBR_f& operator+=(const RGBR_f& right)
    {
        r += right.r;
        g += right.g;
        b += right.b;
        a += right.a;
        return *this;
    }

    inline RGBR_f& operator/=(double right) {
        r /= right;
        g /= right;
        b /= right;
        a /= right;
        return *this;
    }

    inline RGBR_f& operator*=(double right) {
        r *= right;
        g *= right;
        b *= right;
        a *= right;
        return *this;
    }

    float r;
    float g;
    float b;
    float a;
};

inline RGBR_f operator*(const RGBR_f& left, double right) {
    RGBR_f newColor(left.r * right, left.g * right, left.b * right, left.a);
    return newColor;
}

inline RGBR_f operator*(const RGBR_f& left, const RGBR_f& right) {
    RGBR_f newColor(left.r * right.r, left.g * right.g, left.b * right.b, left.a);
    return newColor;
}

#endif //_RGBRF_H
