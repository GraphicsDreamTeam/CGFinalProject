//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.cpp
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#include "Camera.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "STMatrix4.h"
#include "STVector3.h"

Camera::Camera(STVector3 lookat, STVector3 position, STVector3 up)
{
    SetLookAt(lookat);
    SetPosition(position);
    SetUp(up);
    SetFov(90);
}

Camera::~Camera()
{

}

// set the up and right vectors
void Camera::SetUpAndRight(void)
{

    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}


// reset the camera position
void Camera::Reset(void)
{
    m_Position = STVector3(0.f, 0.f, 1.f);
    m_LookAt = STVector3(0.f,0.f,0.f);

    m_Up = STVector3(0.f,1.f,-1.f);
    m_Up.Normalize();

    SetUpAndRight();
}

void Camera::SetFov(int newFov) {
    fov = newFov;
}

int Camera::GetFov(void) {
    return fov;
}

// reset the camera up vector
void Camera::ResetUp(void)
{
    m_Up = STVector3(5.f,5.f,0.f);
    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}


//
// Rotate the camera
void Camera::Rotate(float delta_x, float delta_y)
{
    float yaw_rate=1.f;
    float pitch_rate=1.f;

    m_Position -= m_LookAt;
    STMatrix4 m;
    m.EncodeR(-1*delta_x*yaw_rate, m_Up);
    m_Position = m * m_Position;
    m.EncodeR(-1*delta_y*pitch_rate, m_Right);
    m_Position = m * m_Position;

    m_Position += m_LookAt;
}


//
// This controlls camera zoom
//
void Camera::Zoom(float delta_y)
{
    STVector3 direction = m_LookAt - m_Position;
    float magnitude = direction.Length();
    direction.Normalize();
    float zoom_rate = 0.1f*magnitude < 0.5f ? .1f*magnitude : .5f;
    if(delta_y * zoom_rate + magnitude > 0)
    {
        m_Position += (delta_y * zoom_rate) * direction;
    }
}


//
// This moves the camera left and right
//
void Camera::Strafe(float delta_x, float delta_y)
{
    float strafe_rate = 0.05f;

    m_Position -= strafe_rate * delta_x * m_Right;
    m_LookAt   -= strafe_rate * delta_x * m_Right;
    m_Position += strafe_rate * delta_y * m_Up;
    m_LookAt   += strafe_rate * delta_y * m_Up;
}


// This is the 3D position of the camera in space
//
STVector3 Camera::Position (void)
{
    return(m_Position);
}


// set the look at vector w
// the viewing direction is -w
STVector3 Camera::LookAt (void)
{
    return(m_LookAt);
}


// sets the up vector v
STVector3 Camera::Up (void)
{
    return(m_Up);
}


STVector3 Camera::Right(void) {
    return (m_Right);
}

STVector3 Camera::SetPosition(float x, float y, float z) { SetPosition(STVector3(x,y,z)); }
STVector3 Camera::SetPosition(STVector3 newPos) {
    m_Position.x = newPos.x;
    m_Position.y = newPos.y;
    m_Position.z = newPos.z;

    SetUpAndRight();
}

STVector3 Camera::SetLookAt(float x, float y, float z) { SetLookAt(STVector3(x, y, z)); }
STVector3 Camera::SetLookAt(STVector3 newLookAt) {
    m_LookAt.x = newLookAt.x;
    m_LookAt.y = newLookAt.y;
    m_LookAt.z = newLookAt.z;
    SetUpAndRight();
}

void Camera::SetUp(STVector3 newUp) {
    m_Up = newUp;
    SetUpAndRight();
}