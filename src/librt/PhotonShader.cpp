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
        if(((pIntersection->point - photons->at(i)->GetIntersection().point)).LengthSq() <= 0.7){
            float weight = std::max(0.0f, STVector3::Dot(surfNorm, photons->at(i)->GetDirection()));
            weight *= (5.0f - sqrt(photons->at(i)->GetDistSquared())) / 5.0f;

            photonColor += (photons->at(i)->GetColor() * weight);
            photonColor = RGBR_f::Min(pIntersection->surface->GetColor(), photonColor);
        }
    }
    return photonColor;
}