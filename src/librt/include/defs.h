//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Defs.h
// Global Definitions
//------------------------------------------------------------------------------


#ifndef __DEFS_H__
#define __DEFS_H__

#include <vector>
#include "Light.h"
#include "Intersection.h"



// render modes for the raytracer class
// determines the type of image created
typedef enum {
	METAL,
	MATTE,
	GLASS
	// Metal = Phong(1.5, 0.9);
    // HIT				= 1,
    // LAMBERTIAN      = 2,
    // PHONG           = 3
} Materials;



// TO DO: Proj2 raytracer
// Add constant parameters for special effects.
// 1. Add any constant parameters that may be useful for your
//    special effect. Some examples are added below.
//------------------------------------------------
//------------------------------------------------
const double EPSILON = 1.0e-6;
const double REFRACT_INDEX_VACUUM           = 1.0000;
const double REFRACT_INDEX_AIR              = 1.0003;
const double REFRACT_INDEX_WATER            = 1.3330;
const double REFRACT_INDEX_GLASS            = 1.5500;
const double REFRACT_INDEX_MIN              = 1.0000;
const double REFRACT_INDEX_MAX              = 9.0000;



#endif //__DEFS_H__

