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
#include <cmath>

Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}


// Runs the shader according to the specified render mode
RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection, light, pScene);
            break;
        case PHONG:
            color = Phong(pIntersection, lightDirection, light, pScene);
            break;
        case HIT:
            color = Hit(pIntersection, lightDirection, light, pScene);
            break;
        case PHOTON:
            color = Photon(pIntersection, lightDirection, light,pScene);
            break;
        default:
            color = Hit(pIntersection, lightDirection, light, pScene);
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
RGBR_f Shader::Hit(Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene)
{
    assert(pIntersection);
    assert(lightDirection);

    return RGBR_f(255, 0, 0, 1);
}



// Implements a simple red colorer if we hit something.
RGBR_f Shader::Photon(Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene)
{
   // assert(pIntersection);
   // assert(lightDirection);

    RGBR_f color = RGBR_f(0,0,0,255);

        //    std::cout<<"PHOTONS:"<<pScene->GetPhotons()->size()<<"\n";

    for(int i=0;i<pScene->GetPhotons()->size();i++){

        if((pScene->GetPhotons()->at(i)->GetIntersection().point - pIntersection->point).LengthSq() <= 0.001){
            color += RGBR_f(5,0,0,255);
        }

    }

    return color;
}





// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene)
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
RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f finalColor;
    //RGBR_f photonColor = gatherPhotons(pIntersection); //merge in the photon color how?
    // Ambient
    // Handled in raytracer

    // Diffuse component
    RGBR_f diffuseColor = Lambertian(pIntersection, lightDirection, light, pScene);

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

    //finalColor += photonColor;      //added Nathan
    finalColor += diffuseColor;
    finalColor += specularColor;

    return(finalColor);
}

/////
// below is photon mapping code
/////

/*RGBR_f gatherPhotons(Intersection *pIntersection){
  RGBR_f photonColor(0.0,0.0,0.0,255.0);  
  STVector3 N = pIntersection->normal;                   //Surface Normal at Current Point
  for (int i = 0; i < numPhotons[type][id]; i++){                    //Photons Which Hit Current Object
    if (gatedSqDist3(pIntersection,photons[type][id][i][0],sqRadius)){           //Is Photon Close to Point?
      float weight = max(0.0, -dot3(N, photons[type][id][i][1] ));   //Single Photon Diffuse Lighting
      weight *= (1.0 - sqrt(gSqDist)) / exposure;                    //Weight by Photon-Point Distance
      photonColor = add3(photonColor, mul3c(photons[type][id][i][2], weight)); //Add Photon's color to Total
   }} 
  return photonColor;
}*/








Shader::~Shader()
{
}


// TO DO: Proj2 raytracer
//          - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------

