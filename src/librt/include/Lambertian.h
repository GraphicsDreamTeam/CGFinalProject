//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Lambertian.h
// Computes Shading
// RenderMode mode determines the type of shading algorithm used
// Given a normal, light direction, color and other shading input
//------------------------------------------------------------------------------------------------


#ifndef _LAMBERTIAN_H
#define _LAMBERTIAN_H

#include "STVector3.h"
#include "defs.h"


class Intersection;


class Lambertian : public Shader {

public:

                                        Lambertian                       (float diffuseValue, float specularColor);
                                        ~Lambertian                      (void);

    virtual RGBR_f                      Shade                        (Intersection *pIntersection, STVector3 *lightDirection, Light *light);

private:

	float diffuseValue
	float specularValue

};


#endif //_LAMBERTIAN_H