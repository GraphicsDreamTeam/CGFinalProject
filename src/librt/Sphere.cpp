//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"
#include "RGBR_f.h"
#include <cmath>

// constructor
Sphere::Sphere(void)
    : m_radius(0.5)
{
      m_center = STVector3(0,0,0);
}

Sphere::Sphere(STVector3 newVector, float radius, RGBR_f color, Material material) : m_radius(radius) {
    m_center = newVector;
    SetColor(color);
    SetMaterial(material);
}

// clean up here
Sphere::~Sphere()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection)
{
    STVector3 L = m_center - ray.Origin();
    double t_ca = STVector3::Dot(L, ray.Direction());

    if (t_ca < 0) {
        return false;
    }

    double d = sqrt(L.LengthSq() - pow(t_ca, 2.0));

    if (d > m_radius) {
        return false;
    } else if (d == m_radius) { // tangent, one hit, but we ignore that

        // double t = t_ca;
        // STVector3 point = ray.Origin() + ray.Direction()*t;
        // STVector3 normal = (point - m_center);
        // normal.Normalize();

        // pIntersection->distanceSqu = pow(t, 2.0);
        // pIntersection->surface = this;
        // pIntersection->point = point;
        // pIntersection->normal = normal;
        // pIntersection->cameraLookingDirection = ray.Direction();

        return false;
    } else { // two hits

        double t_hc = sqrt(pow(m_radius, 2.0) - pow(d, 2.0));

        double t0 = t_ca - t_hc;
        double t1 = t_ca + t_hc;
        double t = t0 < t1 ? t0 : t1;
        STVector3 point = ray.Origin() + ray.Direction() * t;
        STVector3 normal = (point - m_center);
        normal.Normalize();

        pIntersection->distanceSqu = pow(t, 2.0);
        pIntersection->surface = this;
        pIntersection->point = point;
        pIntersection->normal = normal;
        pIntersection->cameraLookingDirection = ray.Direction();

        return true;
    }

   return false;
}

