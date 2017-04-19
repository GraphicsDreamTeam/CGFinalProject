#include "Lambertian.h"
#include "STVector3.h"
#include "RGBR_f.h"
#include "Surface.h"
#include <stdio.h>

Lambertian::Lambertian (float diffuseValue) : diffuseValue(diffuseValue)
{

}

RGBR_f Lambertian::Shade (Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
	double diffuseFactor = std::max(0.0f, STVector3::Dot(pIntersection->normal, *lightDirection));
	diffuseFactor *= light->GetIntensity(pIntersection->point); // How Intensity effects the light
	diffuseFactor *= diffuseValue; // How the lambert diffuse coefficient effects the light

	RGBR_f reflectedColor = RGBR_f::Min(pIntersection->surface->GetColor(), light->GetColor()); // or multiplicative average?
	RGBR_f diffuseColor = reflectedColor * diffuseFactor;

	// Arbitrarily set the alpha to 255.
	diffuseColor.a = 255;

	return diffuseColor;
}