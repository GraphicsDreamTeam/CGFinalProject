

#ifndef __PHOTON_H__
#define __PHOTON_H__


#include "STVector3.h"
#include "RGBR_f.h"

//class Surface;

class Photon {

public:

                    Photon                       (void);
                    ~Photon                      (void);
    RGBR_f 			rgb;
    STVector3       origin;
    STVector3       direction;
};


#endif //__PHOTON_H__
