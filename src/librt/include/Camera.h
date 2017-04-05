//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.h
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "STVector3.h"

class Camera
{

public:
                            Camera(STVector3 lookat, STVector3 position, STVector3 up);
                            ~Camera(void);

    void                    Reset                                       (void);
    void                    ResetUp                                     (void);
    void                    SetUpAndRight                               (void);
    void                    Strafe                                      (float delta_x, float delta_y);
    void                    Zoom                                        (float delta_y);
    void                    Rotate                                      (float delta_x, float delta_y);

    STVector3               SetPosition                                 (float x, float y, float z);
    STVector3               SetPosition                                 (STVector3           newPos);
    STVector3               SetLookAt                                   (float x, float y, float z);
    STVector3               SetLookAt                                   (STVector3 newLookAt);
    void                    SetFov                                      (int fov);
    void                    SetUp                                       (STVector3 newUp);


    STVector3               Right                                       (void);
    STVector3               Position                                    (void);
    STVector3               LookAt                                      (void);
    STVector3               Up                                          (void);
    int                     GetFov                                      (void);

private:

    // parameters
    STVector3               m_Position;
    STVector3               m_LookAt;
    STVector3               m_Right;
    STVector3               m_Up;
    int                     fov;


    void                    Init                                        (void);

};


#endif //__CAMERA_H__

