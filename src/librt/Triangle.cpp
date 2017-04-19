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

// contructor
Triangle::Triangle(void)
        : Surface()
{

}

Triangle::Triangle(STVector3 m_a_in, STVector3 m_b_in, STVector3 m_c_in, RGBR_f color_in, Material material) : m_a(m_a_in), m_b(m_b_in), m_c(m_c_in) {
    SetColor(color_in);
    SetMaterial(material);
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

    double denom = STVector3::Dot(N, N);

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

    // Next assunimg we are valid, we now have a point that we hit and need to determine if
    // it happens within the bounds of the triangle

    double ABCArea = findTriangleArea(m_a, m_b, m_c);
    double ABPArea = findTriangleArea(m_a, m_b, P);
    double BCPArea = findTriangleArea(m_b, m_c, P);
    double CAPArea = findTriangleArea(m_c, m_a, P);

    double u = CAPArea / ABCArea;
    double v = ABPArea / ABCArea;
    double w = BCPArea / ABCArea;

    double maxValue = std::max<double>(u, std::max<double>(v, w));
    double minValue = std::min<double>(u, std::min<double>(v, w));

    // std::cout << m_a.x << " " << m_a.y << " " << m_a.z << std::endl;
    // std::cout << P.x << " " << P.y << " " << P.z << std::endl;

    // std::cout << ABPArea << std::endl;

    if ((u < -0.5 && u > 1.5) | (v < -0.5 && v > 1.5) | (w < -0.5 && w > 1.5)) {
        std::cout << u << " | " << v << " | " << w << std::endl;
    }

    if (maxValue > 1 || minValue < 0) // Point lies outside the triangle
    {
        return false;
    }

    // Finally, if control reachest here, we've hit the plane, and it's within the triangle.
    // Now we load the information we need into the intersection object

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
    STVector3 ba = m_b - m_a;
    STVector3 ca = m_c - m_a;
    STVector3 normal = STVector3::Cross(ba, ca);
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