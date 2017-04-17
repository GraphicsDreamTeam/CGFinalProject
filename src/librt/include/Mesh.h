//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Mesh.h
// Defines a Mesh surface enclosed by N triangles
//-----------------------------------------------------------------------------


#ifndef __MESH_H__
#define __MESH_H__



#include "Surface.h"
#include "Triangle.h"
#include <vector>
#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"
#include <string.h>


class Mesh : public Surface
{

public:
                                Mesh                        (void);
                                Mesh                        (const std::string& fileName, STVector3 position_in, RGBR_f color_in);
                                ~Mesh                       (void);

    bool                        FindIntersection            (Ray ray, Intersection *pIntersection);



private:

    // component triangles
    std::vector<Triangle*>          triangles;
    STVector3						position;
    void                            readFile(const std::string& fileName);

};


#endif //__MESH_H__

