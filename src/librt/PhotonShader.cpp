#include "PhotonShader.h"
#include "STVector3.h"
#include "RGBR_f.h"
#include "Surface.h"
#include <stdio.h>
#include <cmath>

PhotonShader::PhotonShader (void)
{

}

RGBR_f PhotonShader::Shade (Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene *pScene)
{
	RGBR_f photonColor;

    std::vector<Photon*> *photons = pScene->GetPhotons();

    STVector3 surfNorm = pIntersection->normal;


    for(int i = 0; i < photons->size(); i++){
    float distance = ((pIntersection->point - photons->at(i)->GetIntersection().point)).LengthSq();

        if(distance <= 0.07){
            float weight = std::max(0.0f, STVector3::Dot(surfNorm, photons->at(i)->GetDirection()));
            weight *= (1.0f - sqrt(photons->at(i)->GetDistSquared())) / 25.0f;

            float weight2 = pow((1.0f - (distance / 0.07f)), 2.0);

            photonColor += (photons->at(i)->GetColor() * weight * weight2);
           
        }
    }
     photonColor = RGBR_f::Min(pIntersection->surface->GetColor(), photonColor);
    return photonColor;
}