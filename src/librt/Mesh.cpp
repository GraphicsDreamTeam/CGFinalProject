//----------------------------------------------------------------
// Mesh.cpp
// Copyright: Corey Toler-Franklin, University of Florida
//
// Mesh surface class
// This class is represented by the surface enclosed by N triangles
//----------------------------------------------------------------
#include "Mesh.h"
#include "STVector3.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include "Triangle.h"
#include "Surface.h"
#include <stdexcept>
#include "Intersection.h"
#include "Material.h"


Mesh::Mesh(const std::string& fileName, STVector3 position_in, RGBR_f color_in, Material material) : position(position_in)
{
    SetColor(color_in);
    SetMaterial(material);
    readFile(fileName);
}

Mesh::~Mesh()
{
    for(unsigned int i = 0; i < triangles.size(); i++) delete triangles[i];
}

bool Mesh::FindIntersection(Ray ray, Intersection *pIntersection)
{
    bool hit = false;
    Intersection* closestIntersection = NULL;
    Intersection* currentIntersection = NULL;

    for (std::vector<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); ++it)
    {
        currentIntersection = new Intersection();

        if ((*it)->FindIntersection(ray, currentIntersection))
        {
            // If control reaches here we have contact between the ray and this particular triangle
            hit = true;

            if (closestIntersection == NULL)
            {
                closestIntersection = new Intersection();
                closestIntersection->distanceSqu = currentIntersection->distanceSqu;
                closestIntersection->point = currentIntersection->point;
                closestIntersection->normal = currentIntersection->normal;
                closestIntersection->cameraLookingDirection = currentIntersection->cameraLookingDirection;
            } else if (currentIntersection->distanceSqu < closestIntersection->distanceSqu)
            {
                closestIntersection->distanceSqu = currentIntersection->distanceSqu;
                closestIntersection->point = currentIntersection->point;
                closestIntersection->normal = currentIntersection->normal;
                closestIntersection->cameraLookingDirection = currentIntersection->cameraLookingDirection;
            }
        }

        delete currentIntersection;
    }

    if (hit)
    {
        pIntersection->distanceSqu = closestIntersection->distanceSqu;
        pIntersection->surface = this;
        pIntersection->point = closestIntersection->point;
        pIntersection->normal = closestIntersection->normal;
        pIntersection->cameraLookingDirection = closestIntersection->cameraLookingDirection;
    }

    delete closestIntersection;

    return hit;
}

void Mesh::readFile(const std::string& fileName)
{
    std::vector<STVector3> mVertices;

    std::cout << "Mesh:" << std::endl;

    std::string ext = STGetExtension(fileName);
    if (!ext.compare("OBJ"))
    {
        std::ifstream in(fileName.c_str(), std::ios::in);

        if(!in)
        {
            throw std::invalid_argument("Error in file input stream for " + fileName);
        }

        char comments[256];
        char token[128];
        float x,y,z;
        int p1,p2,p3;

        while(in >> token)
        {
            if(!strcmp(token, "#"))
            {
                in.getline(comments, 256);
            }
            else if(!strcmp(token, "v"))
            {
                in >> x >> y >> z;
                x += position.x;
                y += position.y;
                z += position.z;
                mVertices.push_back(STVector3(x, y, z));
            }
            else if(!strcmp(token, "f"))
            {
                in >> p1; in.ignore(100, ' ');
                in >> p2; in.ignore(100, ' ');
                in >> p3;

                std::cout << "\tTriangle #" << (triangles.size() + 1) << ": " << std::endl;
                std::cout << "\t\tVertex 1: " << mVertices[p1 - 1] << std::endl;
                std::cout << "\t\tVertex 2: " << mVertices[p2 - 1] << std::endl;
                std::cout << "\t\tVertex 3: " << mVertices[p3 - 1] << std::endl;

                triangles.push_back(new Triangle(mVertices[p1 - 1], mVertices[p2 - 1], mVertices[p3 - 1], GetColor(), GetMaterial()));
            }
        }
    }
    else
    {
        throw std::invalid_argument("Unknown object file type " + fileName);
    }
}