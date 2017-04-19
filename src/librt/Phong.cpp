#include "Phong.h"
#include "STVector3.h"
#include "RGBR_f.h"
#include "Surface.h"
#include "Lambertian.h"
#include <stdio.h>

Phong::Phong (float diffuseValue, float specularValue) : diffuseValue(diffuseValue), specularValue(specularValue)
{

}

RGBR_f Phong::Shade (Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
	RGBR_f finalColor;

    // Ambient
    // Handled in raytracer

    // Diffuse component
    RGBR_f diffuseColor = Lambertian(diffuseValue).Shade(pIntersection, lightDirection, light);

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

    return finalColor;
}