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
    void                    SetFov                                      (int fov);

    STVector3               GetPosition                                 (void);
    STVector3               GetLookAt                                   (void);
    STVector3               GetUp                                       (void);
    int                     GetFov                                      (void);
    void                    SetPosition                                 (STVector3 newPosition);
    void                    SetLookAt                                   (STVector3 newLookAt);
    void                    SetUp                                       (STVector3 newUp);

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

