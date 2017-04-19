//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------

#include "RayTracer.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "utilities.h"
#include "STImage.h"
#include "Shader.h"
#include "STColor4ub.h"
#include <ctime>
#include <cstdlib>
#include "Surface.h"
#include "Sphere.h"
#include "STVector2.h"
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

RayTracer::RayTracer(void)
    : m_maxLevel            (20),
     m_intensityThreshold   (0.001)
{
    pShader = new Shader();
}


RayTracer::~RayTracer()
{

}

//------------------------------------------------
// Main raytracing algorithm
// Cast Ray, Compute Intersections, Shade pixel
//-----------------------------------------------
void RayTracer::Run(Scene *pScene, STVector2* imageSize, std::string fName)
{


    this->emitPhotons(pScene,2000, 4);
    //

    this->rayTrace(pScene, imageSize,fName);

}

RGBR_f RayTracer::Shade(Scene *pScene, Intersection *pIntersection)
{
    LightList* sceneLightList = pScene->GetLightList();
    SurfaceList* surfaceList = pScene->GetSurfaceList();
    STVector3 shadowOrigin = pIntersection->point;

    RGBR_f color = RGBR_f(20, 20, 20, 255);

    for (int l = 0; l < sceneLightList->size(); l++) {
        Light light = sceneLightList->at(l);

        STVector3 shadowDirection = light.GetPosition() - pIntersection->point;
        shadowDirection.Normalize();

        Ray ray = Ray();
        ray.SetOrigin(shadowOrigin);
        ray.SetDirection(shadowDirection);
        Intersection intersection;

        for (int s = 0; s < surfaceList->size(); s++) { // Iterate over surfaces
            Surface* surface = surfaceList->at(s);

            if (surface != pIntersection->surface) {

                if (surface->FindIntersection(ray, &intersection)) {
                    goto LightLoop;
                }
            }
        }

        color += pIntersection->surface->GetMaterial().Shade(pIntersection, &shadowDirection, &light);

        LightLoop:
        continue;
    }

    return(color);
}


//------------------------------------------------------
// Always render with a minimum color so that the scene
// is not black
//------------------------------------------------------
bool RayTracer::MinimumColor(RGBR_f color)
{
    if((color.r  >= m_intensityThreshold) ||
       (color.g >= m_intensityThreshold) ||
       (color.b >= m_intensityThreshold)) {
        return(true);
    }


    return(false);
}


//photon tracer function
bool RayTracer::photonTrace(Scene *pScene, Photon *photon){

            bool result;

            photon->GetDirection().Normalize();                                                            // normalize the direction bc why not

            Ray ray = Ray();
            ray.SetOrigin(photon->GetOrigin());
            ray.SetDirection(photon->GetDirection());

            Intersection* closestIntersection = NULL;

            for (int k = 0; k < pScene->GetSurfaceList()->size(); k++) {

                Intersection* returnIntersection = new Intersection();

                Surface* surface = pScene->GetSurfaceList()->at(k);

                result = surface->FindIntersection(ray, returnIntersection);

                if (result) {

                    if (closestIntersection == NULL) {
                        closestIntersection = returnIntersection;
                    } else if (returnIntersection->distanceSqu < closestIntersection->distanceSqu) {
                        delete closestIntersection;
                        closestIntersection = returnIntersection;
                    }
                } else {
                    delete returnIntersection;
                }

            }

            if (closestIntersection == NULL) {
                //std::cout<<"::no intersection found:: \n";
                return false;
            }else{
                photon->SetIntersection(*closestIntersection);
                //std::cout<<"::Intersection Found:: "<<photon->GetIntersection().point.x<<","<<photon->GetIntersection().point.y<<","<<photon->GetIntersection().point.z<<"\n";
                result = true;
            }
           // std::cout<<result<<"result of photonTrace \n";
            return result;
}









void RayTracer::rayTrace(Scene *pScene, STVector2* imageSize, std::string fName){
    // begin
    std::cout << "Running... " << std::endl;

    // Clock stuff for timing it!
    std::clock_t start;
    double duration;
    start = std::clock();

    // the color redult from shading
    RGBR_f color;

    SurfaceList* surfaceList = pScene->GetSurfaceList();

    int width = imageSize->x;
    int height = imageSize->y;
    RGBR_f bkground = pScene->GetBackgroundColor();
    STImage *pImg = new STImage(width, height, STImage::Pixel(bkground.r*255, bkground.g*255, bkground.b*255, bkground.a*255));

    double aspectRatio = ((double) width) / ((double) height);
    double scale = tan(((double) pScene->GetCamera()->GetFov()) / 2.0 * M_PI / 180);

    // STVector3 rayOrigin = pScene->GetCamera()->GetPosition(); // Perspective

    /*STVector3 imagePoint = widthD * pScene->GetCamera()->Right() +
                    heightD * pScene->GetCamera()->Up() +
                    pScene->GetCamera()->Position() + pScene->GetCamera()->LookAt();*/

    STVector3 rayDirection(0, 0, 1); // Orthagonal

    int numRaysHit = 0;
    int numRays = 0;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double pX = (2.0 * ((((double) i) + 0.5) / width) - 1.0) * scale * aspectRatio; // Perspective
            double pY = (1.0 - 2.0 * ((((double) j) + 0.5) / height)) * scale; // Perspective

            STVector3 rayOrigin = pX * pScene->GetCamera()->Right() +
                pY * pScene->GetCamera()->Up() +
                pScene->GetCamera()->Position() + pScene->GetCamera()->LookAt();

            STVector3 rayDirection = rayOrigin - pScene->GetCamera()->Position();
            rayDirection.Normalize();

            Ray ray = Ray();
            ray.SetOrigin(rayOrigin);
            ray.SetDirection(rayDirection);

            Intersection* closestIntersection = NULL;

            for (int k = 0; k < surfaceList->size(); k++) {
                Intersection* returnIntersection = new Intersection();
                Surface* surface = (*surfaceList)[k];

                bool result = surface->FindIntersection(ray, returnIntersection);

                if (result) {
                    numRaysHit++;

                    if (closestIntersection == NULL) {
                        closestIntersection = returnIntersection;
                    } else if (returnIntersection->distanceSqu < closestIntersection->distanceSqu) {
                        delete closestIntersection;
                        closestIntersection = returnIntersection;
                    }
                } else {
                    delete returnIntersection;
                }

                numRays++;
            }

            if (closestIntersection != NULL) { // We hit something! calculate the pixel color at that point
                RGBR_f color = Shade(pScene, closestIntersection);
                int clamped_r = std::max(0.0f, std::min(color.r, 255.0f));
                int clamped_g = std::max(0.0f, std::min(color.g, 255.0f));
                int clamped_b = std::max(0.0f, std::min(color.b, 255.0f));
                pImg->SetPixel(i, j, STImage::Pixel(clamped_r, clamped_g, clamped_b, 255));
            }
        }
    }

    Camera* sceneCamera = pScene->GetCamera();

    // End the clock timer and get its duration
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    // end
    std::cout << "DONE... (Elapsed time: " << duration * 1000 << " ms, hit: " << ((((double) numRaysHit) / ((double) numRays)) * 100) << "% (" << numRaysHit << " / " << numRays << "))" << std::endl;

    // save
    pImg->Save(fName);
    std::cout << "saved file " << fName.c_str() << std::endl;
}


void RayTracer::emitPhotons(Scene *pScene, int nrPhotons, int numBounces){


    srand (time(NULL));                          //Ensure Same Photons Each Time, should make this settable in setup


//  for (int t = 0; t < nrTypes; t++)            //Initialize Photon Count to Zero for Each Object
//    for (int i = 0; i < nrObjects[t]; i++)
//      numPhotons[t][i] = 0;

for(int l = 0;l<pScene->GetLightList()->size();l++){ // go through the number of lights >>IS THIS A GOOD IDEA?<<

  for (int i = 0; i < nrPhotons; i++){                  //shoot the number of photons
    int bounces = 1;


    STVector3 initDirection = STVector3( -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1)))), -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1)))), -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1)))) );
    //std::cout<<-1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1))))<<"\n";

    initDirection.Normalize();

    Photon *photon = new Photon(pScene->GetLightList()->at(l).GetColor(),initDirection, pScene->GetLightList()->at(l).GetPosition(),numBounces);// continue work from here.  need to save photons somehow


    //Spread Out Light Source, But Don't Allow Photons Outside Room/Inside Sphere
  //  while (prevPoint[1] >= Light[1]){ prevPoint = add3(Light, STVector3( rand() % 1 - 1,rand() % 1 - 1,rand() % 1 - 1 ).Normalize() * 0.75);}
   // if (abs(prevPoint[0]) > 1.5 || abs(prevPoint[1]) > 1.2 ) bounces = nrBounces+1;


    bool hit = photonTrace(pScene,photon);                          //Trace the Photon's Path

   // std::cout<<hit<<" :boolean value \n";

   if (hit == true)
   {

    while (hit && photon->GetCurrentBounces() <= photon->GetMaxBounces()){        //Intersection With New Object
        //rgb = mul3c (getColor(rgb,gType,gIndex), 1.0/sqrt(bounces));
        photon->GetColor() = photon->GetIntersection().surface->GetColor() * (1.0/sqrt(photon->GetCurrentBounces()));
        //shadowPhoton(ray);                             //Shadow Photon
        //reflect(ray,prevPoint);                  //Bounce the Photon
        photon->Reflect();
        hit = photonTrace(pScene,photon);                         //Trace It to Next Location
        photon->currentBounces++;
    }
        //std::cout<<"found an intersection, lets add it \n";
        pScene->GetPhotons()->push_back(photon);                //once bouncing is done save the photon to the scene
       // std::cout<<"size:"<<pScene->GetPhotons()->size()<<"\n";
    }

  }
}
}