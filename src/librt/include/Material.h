//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Material.h
// Defines the base class for surfaces
//-----------------------------------------------------------------------------

#ifndef _MATERIAL_H
#define _MATERIAL_H


#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"
#include "defs.h"
#include "Lists.h"
#include "Material.h"


class Material
{

    public:

                                    Material                             (Shader shader);
                                    ~Material                            (void);

    virtual RGBR_f                  Shade                                (Intersection *pIntersection, STVector3 *lightDirection, Light *light) { return RGBR_f(0, 0, 0, 0) }

protected:

    Shader                          m_shader;

};


#endif //_MATERIAL_H



