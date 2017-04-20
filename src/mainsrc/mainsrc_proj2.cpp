//--------------------------------------------------------
// Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#ifndef GLEW_STATIC
    #define GLEW_STATIC 1
#endif
#include "stglew.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include "Scene.h"
#include "RayTracer.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "defs.h"
#include "Mesh.h"
#include "Shader.h"
#include "Phong.h"
#include "Material.h"
#include "Lambertian.h"

// globals
//---------------------------------
// scene
Scene       *pScene = NULL;     // scene geometry and lights
RayTracer   *pRayTracer = NULL; // runs ray tracing algorithm
STVector2   *imageSize;

// mouse
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

// Window size, kept for screenshots
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;

void SpecialKeyCallback(int key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);

//---------------------------------------------------------------------
// Scene functions
//---------------------------------------------------------------------
// Creates the scene
//
void Setup(void)
{
    // renderMode = HIT;
    // renderMode = LAMBERTIAN;
    // renderMode = PHONG;

    Material metal = Material(new Phong(1.5, 0.9));
    Material plastic = Material(new Lambertian(1.5));

    // We set the image size here because it makes the most sense.
    imageSize = new STVector2(1000, 1000);

    pScene = new Scene();
    pRayTracer = new RayTracer();

    STVector3 cameraPosition(10, 5, 0);
    STVector3 cameraLookAt = STVector3::Zero - cameraPosition;
    cameraLookAt.Normalize();

    Camera* camera = new Camera(cameraLookAt, cameraPosition, STVector3(1.0f, 0.0f, 0.0f));
    camera->SetFov(100);

    pScene->SetCamera(camera);
    pScene->SetBackgroundColor(RGBR_f(0, 0, 0, 1)); // Does nothing right now
    // pScene->AddLight(Light(STVector3(-1.5, 0, 0), RGBR_f(255, 255, 255, 255), 10, "Light1"));
    pScene->AddLight(Light(STVector3(5, -3, -3), RGBR_f(0, 0, 255, 255), 10, "Light1"));
    pScene->AddLight(Light(STVector3(5, 3, 3), RGBR_f(255, 0, 0, 255), 10, "Light2"));
    pScene->AddLight(Light(STVector3(5, 3, -3), RGBR_f(0, 255, 0, 255), 10, "Light3"));
    pScene->AddLight(Light(STVector3(5, -3, 3), RGBR_f(255, 255, 0, 255), 10, "Light4"));
    pScene->AddSurface(new Sphere(STVector3(2.2, 0.15, -1.17), 0.5, RGBR_f(255, 255, 255, 255), metal));
    pScene->AddSurface(new Sphere(STVector3(0, 0, 0), 2, RGBR_f(255, 255, 255, 255), metal));
    pScene->AddSurface(new Mesh("../../data/meshes/bigcubeinverted.obj", STVector3(-13.5, -13.5, -13.5), RGBR_f(255, 255, 255, 255), plastic));
}


void SpecialKeyCallback(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            pScene->GetCamera()->Strafe(10,0);
            break;
        case GLUT_KEY_RIGHT:
            pScene->GetCamera()->Strafe(-10,0);
            break;
        case GLUT_KEY_DOWN:
            pScene->GetCamera()->Strafe(0,-10);
            break;
        case GLUT_KEY_UP:
            pScene->GetCamera()->Strafe(0,10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void KeyCallback(unsigned char key, int x, int y)
{

    switch(key) {
    case 's': {
            //
            // Take a screenshot, and save as screenshot.jpg
            //
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0,0);
            screenshot->Save("../../data/images/screenshot.jpg");
            delete screenshot;
        }
        break;
    case 'r':
        pScene->GetCamera()->Reset();
        break;
    case 'u':
        pScene->GetCamera()->ResetUp();
        break;
    case 'q':
        exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    // Initializes the scene
    Setup();


    // run the ray tracer
    pRayTracer->Run(pScene, imageSize, "output.png");

    return 0;
}


#pragma endregion