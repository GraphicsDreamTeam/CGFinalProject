//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

// Runs the shader according to the specified render mode
/*RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
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

    return(color);
}*/

// Implements a simple red colorer if we hit something.
/*RGBR_f Shader::Hit(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
    assert(pIntersection);
    assert(lightDirection);


    return RGBR_f(255, 0, 0, 255);
}*/



// Implements a simple red colorer if we hit something.
/*RGBR_f Shader::Photon(Intersection *pIntersection, STVector3 *lightDirection, Light *light, Scene* pScene)
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
}*/

// Implements diffuse shading using the lambertian lighting model
/*RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
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
}*/

// Implements diffuse shading using the lambertian lighting model
/*RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
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
}*/