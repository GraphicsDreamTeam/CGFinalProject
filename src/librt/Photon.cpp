

#include "Photon.h"


Photon::Photon(RGBR_f initColor,STVector3 initDirection,STVector3 initOrigin)
    :   rgb         		(initColor),
        direction           (initDirection),
        origin              (initOrigin),
        lastIntersection    (NULL)
{

}


Photon::~Photon(void)
{

}


//set the photon color
void Photon::SetColor(RGBR_f color)
{
    rgb = color;
}


// return the photon color
RGBR_f Photon::GetColor(void)
{
    return(rbg);
}

//set the photon direction
void Photon::SetDirection(STVector3 direc)
{
    direction = direc;
}


// return the photon direction
STVector3 Photon::GetDirection(void)
{
    return(direction);
}

//set the photon origin
void Photon::SetOrigin(STVector3 orig)
{
    origin = orig;
}


// return the photon direction
STVector3 Photon::GetOrigin(void)
{
    return(origin);
}

//set the photon's last intersection
void Photon::SetIntersection(Intersection intersection)
{
    lastIntersection = intersection;
}


// return the photon's last direction
Intersection Photon::GetIntersection(void)
{
    return(lastIntersection);
}