//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Triangle.h
// Defines a triangle surface enclosed by three points m_a, m_b, m_c
//-----------------------------------------------------------------------------


#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__



#include "Surface.h"
#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"



class Triangle : public Surface
{

public:
                                Triangle                        (void);
                                Triangle                        (STVector3 m_a_in, STVector3 m_b_in, STVector3 m_c_in, RGBR_f color_in);
                                ~Triangle                       (void);

    bool                        FindIntersection                (Ray ray, Intersection *pIntersection);



private:


    // vertices
    STVector3                   m_a;
    STVector3                   m_b;
    STVector3                   m_c;


    // linear systems
    bool                        IntersectionSolver              (Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w);

    STVector3                   ComputeNormalVector             (void);

};


#endif //__TRIANGLE_H__

