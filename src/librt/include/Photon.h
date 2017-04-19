

#ifndef __PHOTON_H__
#define __PHOTON_H__


#include "STVector3.h"
#include "RGBR_f.h"
#include "Intersection.h"
//class Surface;

class Photon {

public:

                    Photon                       (RGBR_f initColor,STVector3 initDirection,STVector3 initOrigin, int);
                    ~Photon                      (void);


void 				SetColor					 (RGBR_f color);

RGBR_f 				GetColor					 (void);

void 				SetDirection				 (STVector3 direc);

STVector3 			GetDirection				 (void);

void 				SetOrigin				 	 (STVector3 orig);

STVector3 			GetOrigin				 	 (void);

void 				SetIntersection				 (Intersection intersection);

Intersection 		GetIntersection				 (void);

void 				SetDistSquared				 (float dist);

float		 		GetDistSquared			 	 (void);

void 				SetMaxBounces				 (int num);

int 			 	GetMaxBounces			 	 (void);

void 				SetCurrentBounces			 (int num);

int 			 	GetCurrentBounces			 (void);

void 				updateTrajectory			 (STVector3 direction, STVector3 origin);

void 				Reflect			 			 (void);



    RGBR_f 			rgb;
    STVector3       origin;
    STVector3       direction;
    Intersection    lastIntersection;
    float			distSquared;
    int 			maxBounces;
    int    			currentBounces;
};


#endif //__PHOTON_H__
