//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Sphere.h
// Sphere surface object
//------------------------------------------------------------------------------


#ifndef __SPHERE_H__
#define __SPHERE_H__



#include "Surface.h"
#include "Ray.h"
#include "Intersection.h"
#include "RGBR_f.h"
#include "Material.h"


class Sphere  : public Surface
{

public:
                                Sphere                              (void);
                                Sphere                              (STVector3 newVector, float radius, RGBR_f color, Material material);
                                ~Sphere                             (void);

    bool                FindIntersection                    (Ray ray, Intersection *pIntersection);

private:

    float                       m_radius;


    // TO DO: Proj2 raytracer
    //          - Add object specific properties.
    // 1. Add any object specific properties you need
    //    to create your special effects
    // 2. Remember to initialize these properties in the .cpp file
    //---------------------------------------------------------
    //---------------------------------------------------------
};


#endif //__SPHERE_H__

