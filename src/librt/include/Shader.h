//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.h
// Computes Shading
// RenderMode mode determines the type of shading algorithm used
// Given a normal, light direction, color and other shading input
//------------------------------------------------------------------------------------------------


#ifndef _SHADER_H
#define _SHADER_H

#include "STVector3.h"
#include "defs.h"


class Intersection;


class Shader {

public:

                                        Shader                       (void);
                                        ~Shader                      (void);

    virtual RGBR_f                      Shade                        (Intersection *pIntersection, STVector3 *lightDirection, Light *light);
};


#endif //_RAY_H