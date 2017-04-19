//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Phong.h
// Computes Shading
// RenderMode mode determines the type of shading algorithm used
// Given a normal, light direction, color and other shading input
//------------------------------------------------------------------------------------------------


#ifndef _PHONG_H
#define _PHONG_H

#include "STVector3.h"
#include "defs.h"
#include "Shader.h"

class Phong : public Shader {

public:

                                        Phong                       (float diffuseValue, float specularColor);

            RGBR_f                      Shade                        (Intersection *pIntersection, STVector3 *lightDirection, Light *light);

private:

	float diffuseValue;
	float specularValue;

};


#endif //_PHONG_H