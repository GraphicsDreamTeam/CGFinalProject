//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"
#include <stdio.h>
#include "Surface.h"
#include <algorithm>


Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}


// Runs the shader according to the specified render mode
RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection, light);
            break;
        case PHONG:
            color = Phong(pIntersection, lightDirection, light);
            break;
        case HIT:
            color = Hit(pIntersection, lightDirection, light);
            break;
        default:
            color = Hit(pIntersection, lightDirection, light);
            break;
        }

    // TO DO: Proj2 raytracer
    //          - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}

// Implements a simple red colorer if we hit something.
RGBR_f Shader::Hit(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
    assert(pIntersection);
    assert(lightDirection);

    return RGBR_f(255, 0, 0, 255);
}

// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
    assert(pIntersection);
    assert(lightDirection);

    double diffuseFactor = std::max(0.0f, STVector3::Dot(pIntersection->normal, *lightDirection));
    diffuseFactor *= light->GetIntensity(pIntersection->point); // How Intensity effects the light
    diffuseFactor *= 0.9; // How the lambert diffuse coefficient effects the light

    RGBR_f reflectedColor = RGBR_f::Min(pIntersection->surface->GetColor(), light->GetColor()); // or multiplicative average?
    RGBR_f diffuseColor = reflectedColor * diffuseFactor;

    // Arbitrarily set the alpha to 255.
    diffuseColor.a = 255;

    return(diffuseColor);
}

// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f finalColor;

    // Ambient
    // Handled in raytracer

    // Diffuse component
    RGBR_f diffuseColor = Lambertian(pIntersection, lightDirection, light);

    // Specular component
    STVector3 d = pIntersection->cameraLookingDirection;
    STVector3 n = pIntersection->normal;
    STVector3 r = d - 2 * (STVector3::Dot(d, n) * n);
    r.Normalize();

    double specularFactor = (pow(std::max(0.0f, STVector3::Dot(r, *lightDirection)), 64.0));
    specularFactor *= light->GetIntensity(pIntersection->point); // How Intensity effects the light
    specularFactor *= 1.5; // How the lambert diffuse coefficient effects the light

    RGBR_f reflectedColor = RGBR_f::Min(pIntersection->surface->GetColor(), light->GetColor()); // or multiplicative average?
    RGBR_f specularColor = reflectedColor *= specularFactor;

    finalColor += diffuseColor;
    finalColor += specularColor;

    return(finalColor);
}


Shader::~Shader()
{
}


// TO DO: Proj2 raytracer
//          - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------

