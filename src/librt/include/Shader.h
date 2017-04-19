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
#include "Scene.h"

class Intersection;


class Shader {

public:

                                        Shader                          (void);
                                        ~Shader                         (void);

    void                                SetMode                         (RenderMode mode);

    RGBR_f                               Run                             (Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene);

    // TO DO: Proj2 raytracer
    //          - Add shading functions for special effects.
    // 1. Declare functions for your special effects
    // 2. See the Run function to see when each shading function is called
    //---------------------------------------------------------
    //---------------------------------------------------------


private:

    RenderMode                          m_mode;

    RGBR_f                           Hit                           (Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene);
    RGBR_f                           Lambertian                      (Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene);
    RGBR_f                           Phong                           (Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene);
    RGBR_f                           Photon                           (Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene);

};


#endif //_RAY_H