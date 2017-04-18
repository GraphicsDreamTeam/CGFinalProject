//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------



#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__


#include<string>
#include "defs.h"
#include "Scene.h"
#include "RGBR_f.h"

class Shader;

class RayTracer
{

public:
                                RayTracer                                       (void);
                                ~RayTracer                                      (void);

    void                        Run                                             (Scene *pScene, STVector2* imageSize, std::string fName, RenderMode mode);



private:

    static double const			c2w[4][4];

    Shader                      *pShader;

    int                         m_maxLevel;
    float                       m_intensityThreshold;

    bool                        MinimumColor                                    (RGBR_f color);

    RGBR_f                      Shade                                           (Scene *pScene, Intersection *pIntersection);

    STVector3					multVectMatrix						            (STVector3 rayOrigin);


    void                        rayTrace          (Scene *pScene, STVector2* imageSize, std::string fName, RenderMode mode);
    bool                        photonTrace       (Scene *pScene, Photon *photon);

    void                        emitPhotons       (Scene *pScene, int nrPhotons, int numBounces);
};


#endif //__RAYTRACER_H__

