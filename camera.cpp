#include "camera.h"

Camera::Camera(const V3& eye, float a,
                          float e,
                          float r)

{
    ROLLPI(a); // roll azimuth if is over 360 or < 0
    BLOCKRANGE(e); // block elevation  in within +/- 90 degrees
    _euler.y=a;
    _euler.x=e;
    _euler.z=r;
    _fov = 64.0;   // 64 degrees field of view
    // convert euler angles to forward, side and up vector of the camera
    Euler2Pos();
}

Camera::~Camera()
{
    //dtor
}
