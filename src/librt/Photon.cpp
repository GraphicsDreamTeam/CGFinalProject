

#include "Photon.h"


Photon::Photon(RGBR_f initColor,STVector3 initDirection,STVector3 initOrigin, int numBounces)
    :   rgb         		(initColor),
        direction           (initDirection),
        origin              (initOrigin),
        //lastIntersection    (NULL),
        distSquared			(0),
        maxBounces			(numBounces),
        currentBounces      (0)

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
    return(rgb);
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
	            std::cout<<"before set intersection \n";
    lastIntersection = intersection;
                std::cout<<"after set intersection \n";
}


// return the photon's last intersection
Intersection Photon::GetIntersection(void)
{
    return(lastIntersection);
}


//set distance travelled
void Photon::SetDistSquared(float dist)
{
    distSquared = dist;
}


// return the photon's distance travelled
float Photon::GetDistSquared(void)
{
    return(distSquared);
}

//set the photon's max number of bounces
void Photon::SetMaxBounces(int num)
{
    maxBounces = num;
}


// return the photon's max number of bounces
int Photon::GetMaxBounces(void)
{
    return(maxBounces);
}

//set the photon's current number of bounces
void Photon::SetCurrentBounces(int num)
{
    currentBounces = num;
}


// return the photon's current number of bounces
int Photon::GetCurrentBounces(void)
{
    return(currentBounces);
}


void Photon::Reflect(void)
{
	STVector3 normal = this->GetIntersection().normal;
	STVector3 oldDirection = this->GetDirection();
	STVector3 direction = oldDirection - (normal * (2 * STVector3::Dot(oldDirection, normal)));
	direction.Normalize();
	updateTrajectory(direction,this->GetIntersection().point);
}




// update distance and trajectory
void Photon::updateTrajectory(STVector3 direction, STVector3 origin)
{
   	STVector3 difference = origin-this->origin;		//get the distance vector between the new origin and the old one
    this->distSquared += difference.LengthSq();		//add that distance to the sum
    this->SetOrigin(origin);							//update the new origin
    this->SetDirection(direction);					//update the new direction
}