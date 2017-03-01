//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Light.cpp
// A light object
//------------------------------------------------------------------------------

#include "Light.h"
#include <assert.h>
#include <stdio.h>
#include <string>




Light::Light(STVector3 position, RGBR_f color, int power, std::string id)
    :m_id               (id),
    m_color             (color),
    m_power			    (power),
    m_position          (position)
{

}


Light::~Light()
{

}

//set the light color
void Light::SetColor(RGBR_f color)
{
    m_color = color;
}


// return the light color
RGBR_f Light::GetColor(void)
{
    return(m_color);
}


// set the light position
void Light::SetPosition(STVector3 position)
{
    m_position = position;
}


// return the light position
STVector3 Light::GetPosition(void)
{
    return(m_position);
}

void Light::SetPower(int newPower) {
	m_power = newPower;
}

int Light::GetPower(void) {
	return m_power;
}

double Light::GetIntensity(STVector3 point) {
    double distanceSq = (GetPosition() - point).LengthSq();
    return ((double) GetPower()) / distanceSq;
}






