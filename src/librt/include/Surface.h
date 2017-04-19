//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.h
// Defines the base class for surfaces
//-----------------------------------------------------------------------------

#ifndef _SURFACE_H
#define _SURFACE_H


#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"
#include "defs.h"
#include "Lists.h"
#include "Material.h"
#include "RGBR_f.h"

class Surface
{

    public:
                                    Surface                             (void);
                                    Surface                             (RGBR_f newColor, Material newMaterial);

    virtual bool                    FindIntersection                     (Ray ray, Intersection *pIntersection){ return(false);}
    RGBR_f                          GetColor                            (void);
    void                            SetColor                            (RGBR_f newColor);
    Material                        GetMaterial                         (void);
    void                            SetMaterial                         (Material material_in);

protected:



    STVector3                       m_center;
    RGBR_f                          color;
    Material                        material;

};


#endif //_SURFACE_H



