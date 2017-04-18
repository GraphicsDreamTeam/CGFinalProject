//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
//
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"
#include "STVector3.h"
#include <cmath>
#include "utilities.h"
#include <algorithm>
#include <stdio.h>

#define EPSILON 0.000001

// contructor
Triangle::Triangle(void)
        : Surface()
{

}

Triangle::Triangle(STVector3 m_a_in, STVector3 m_b_in, STVector3 m_c_in, RGBR_f color_in) : m_a(m_a_in), m_b(m_b_in), m_c(m_c_in) {
    SetColor(color_in);
}

// clean up
Triangle::~Triangle()
{

}



//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;

    // TO DO: Proj2 raytracer
    //          - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

    //------------------------------------------------------

    return(bFoundSolution);
}

//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{

    // First, determine where we hit the plane, if at all.
    // Three scenarios can occur
    // 1. We hit it once (what we care about), Good!
    // 2. We hit it many times (we're parallel and in a position to connect with it), ???
    // 3. We never hit it (the ray position and direction mean it will never intersect), ignore

    STVector3 ba = m_b - m_a;
    STVector3 ca = m_c - m_a;

    STVector3 N = STVector3::Cross(ba, ca);

    double intersectionBottom = STVector3::Dot(N, ray.Direction());

    if (!intersectionBottom) // The ray is parallel to the plane and possibly tangential, ignore in all cases.
    {
        return false;
    }

    double d = STVector3::Dot(N, m_a);
    double intersectionTop = STVector3::Dot(N, ray.Origin()) + d;

    double t = -intersectionTop / intersectionBottom;

    if (t < 0) // We're behind the plane, no dice.
    {
        return false;
    }

    // If control reaches here, we've hit the plane, hooray!

    STVector3 P = ray.Origin() + ray.Direction() * t; // The point on the plane that we hit!

    float areaABC = STVector3::Dot(N, STVector3::Cross((m_b - m_a), (m_c - m_a)));
    float areaPBC = STVector3::Dot(N, STVector3::Cross((m_b - P), (m_c - P)));
    float areaPCA = STVector3::Dot(N, STVector3::Cross((m_c - P), (m_a - P)));

    float u = areaPBC / areaABC; // alpha
    float v = areaPCA / areaABC; // beta
    float w = 1.0f - u - v; // gamma

    float maxValue = std::max<float>(u, std::max<float>(v, w));
    float minValue = std::min<float>(u, std::min<float>(v, w));

    if (maxValue > 1 || minValue < 0) // Point lies outside the triangle
    {
        return false;
    }

    pIntersection->distanceSqu = pow(t, 2.0);
    pIntersection->surface = this;
    pIntersection->point = P;
    pIntersection->normal = ComputeNormalVector();
    pIntersection->cameraLookingDirection = ray.Direction();

    return true;
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 ca = m_c - m_a;
    STVector3 ba = m_b - m_a;
    STVector3 normal = STVector3::Cross(ca, ba);
    normal.Normalize();

    return normal;
}


// TO DO: Proj2 raytracer
//          - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
//
//---------------------------------------------------------
//---------------------------------------------------------