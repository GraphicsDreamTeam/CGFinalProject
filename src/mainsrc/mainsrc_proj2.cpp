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
    // We set the image size here because it makes the most sense.
    imageSize = new STVector2(1000, 1000);

    pScene = new Scene();

    STVector3 cameraPosition(0, 0, -5);
    STVector3 cameraLookAt = STVector3::Zero - cameraPosition;
    cameraLookAt.Normalize();

    Camera* camera = new Camera(cameraLookAt, cameraPosition, STVector3(0.0f, 1.0f, -1.0f));
    camera->SetFov(100);

    pScene->SetCamera(camera);

    pScene->SetBackgroundColor(RGBR_f(0, 0, 0, 1));

    pScene->AddLight(Light(STVector3(10, 0, -5), RGBR_f(255, 0, 0, 255), 40, "Light1"));
    pScene->AddLight(Light(STVector3(-10, 0, -5), RGBR_f(0, 0, 255, 255), 40, "Light3"));

    Sphere* sphere1 = new Sphere(STVector3(1.7, 0.15, -1.15), 0.35, RGBR_f(255, 255, 255, 255));
    Sphere* sphere2 = new Sphere(STVector3(0, 0, 0), 0.75, RGBR_f(255, 255, 255, 255));

    pScene->AddSurface(sphere1);
    pScene->AddSurface(sphere2);

    pRayTracer = new RayTracer();

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



// If the commandline input is incorrect, notifies the user.
void usage(const char *myname)
{
    fprintf(stderr, "Usage: %s\nmodes:\n1 Lambertian\n2 Phong\n3 Mirror\n4 Environment Map\n5 Effect_1\n6 Effect_2\n7 Effect_3", myname);
    exit(0);
}


// Parses the input arguments
// The input to the program is a single
// integer value to specify the render mode
RenderMode parseArgs(int argc, char **argv)
{
    if(!(argc == 2))
        usage(argv[0]);

    RenderMode mode = (RenderMode)(atoi(argv[1]));

    if(! ((mode == LAMBERTIAN) ||
        (mode == PHONG) ||
        (mode == MIRROR) ||
        (mode == ENVIRONMENTMAP) ||
        (mode == EFFECT_1) ||
        (mode == EFFECT_2) ||
        (mode == EFFECT_3))) {
            usage(argv[0]);
    }

    return(mode);
}

int main(int argc, char** argv)
{

    RenderMode mode = parseArgs(argc, argv);

    // Initializes the scene
    Setup();

    // run the ray tracer
    pRayTracer->Run(pScene, imageSize, "output.png", mode);

    return 0;
}


#pragma endregion