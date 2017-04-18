//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.cpp
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#include "Scene.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Intersection.h"
#include "Surface.h"
#include "Light.h"
#include "Sphere.h"
#include <vector>
#include "Photon.h"


Scene::Scene(void) : m_background(RGBR_f(0, 0, 0, 1)) {}


Scene::~Scene() {}


void Scene::SetCamera(Camera* camera) {
    delete m_pCamera;
    m_pCamera = camera;
}

void Scene::SetBackgroundColor(RGBR_f color)
{
    m_background = color;
}

//set Photons
void Scene::SetPhotons(std::vector<Photon*> photons)
{
    photonList = photons;
}


RGBR_f Scene::GetBackgroundColor(void)
{
    return(m_background);
}

void Scene::AddLight(Light lightin)
{
    m_lights.push_back(lightin);
}


void Scene::AddSurface(Surface *pSurfacein)
{
    m_surfaceList.push_back(pSurfacein);
}


Camera *Scene::GetCamera(void)
{
    return(m_pCamera);
}

SurfaceList* Scene::GetSurfaceList(void) {
    return &m_surfaceList;
}

LightList* Scene::GetLightList(void) {
    return &m_lights;
}

std::vector<Photon*>* Scene::GetPhotons(void) {
    return &photonList;
}


//-----------------------------------------------------
// clear the scene by removing surfaces
//-----------------------------------------------------
void Scene::Clear(void)
{
    SurfaceList::iterator iter = m_surfaceList.begin();
    SurfaceList::iterator end  = m_surfaceList.end();

    // delete objects
    for (; iter != end; ++iter) {
        delete *iter;
        *iter = NULL;
    }

    // clean up
    m_surfaceList.clear();
}