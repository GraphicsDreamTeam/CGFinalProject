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

double const RayTracer::c2w[4][4] =
{
    {0.4, 0.2, -0.8, 0.0},
    {-0.4, 0.9, 0.0, 0.0},
    {0.8, 0.3, 0.4, 0.0},
    {5.4, 3.0, -1.0, 1.0}
};

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
void RayTracer::Run(Scene *pScene, STVector2* imageSize, std::string fName, RenderMode mode)
{
    // begin
    std::cout << "Running... " << std::endl;

    // Clock stuff for timing it!
    std::clock_t start;
    double duration;
    start = std::clock();

    // the color redult from shading
    RGBR_f color;

    // set the shader's render mode
    pShader->SetMode(mode);

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

        color += pShader->Run(pIntersection, &shadowDirection, &light);

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

STVector3 RayTracer::multVectMatrix(STVector3 rayOrigin) {

    STVector3 output;


}