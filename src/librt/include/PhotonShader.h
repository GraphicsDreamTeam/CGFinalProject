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


#ifndef _PHOTONSHADER_H
#define _PHOTONSHADER_H

#include "STVector3.h"
#include "defs.h"
#include "Shader.h"

class PhotonShader : public Shader {

public:

                                        PhotonShader                 (void);

            RGBR_f                      Shade                        (Intersection *pIntersection, STVector3 *lightDirection, Light *light);

private:


};


#endif //_PHOTONSHADER_H