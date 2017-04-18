//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.cpp
// Base class for all Surfaces
//-------------------------------------------------------------------------------


#include "Surface.h"
#include <assert.h>
#include <stdio.h>
#include <string>


Surface::Surface(void)
{

}


Surface::~Surface()
{

}


RGBR_f Surface::GetColor(void) {
	return color;
}

void Surface::SetColor(RGBR_f newColor) {
	color = newColor;
}

Material Surface::GetMaterial (void)
{
    return material;
}

void Surface::SetMaterial (Material material_in)
{
    material = material_in;
}