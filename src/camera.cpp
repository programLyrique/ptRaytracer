#include "camera.h"

namespace rt
{

    Camera::Camera(Position _eye, Position _centre, vector _up, Scene * par) : eye(_eye), centre(_centre), parent(par), up(_up)
    {

    }

    void Camera::generate(int height, int width)
    {
        
    }

}
