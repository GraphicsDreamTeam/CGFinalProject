//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.cpp
// Base class for all Surfaces
//-------------------------------------------------------------------------------


#include "Surface.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Material.h"
#include "Lambertian.h"

Surface::Surface(void) {
	SetColor(RGBR_f(255, 255, 255, 255));
	// SetMaterial(Material(Lambertian(0.9)));
}

Surface::Surface(RGBR_f newColor, Material newMaterial)
{
    SetColor(newColor);
    SetMaterial(newMaterial);
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