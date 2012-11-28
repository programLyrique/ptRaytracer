#include "camera.h"

namespace rt
{

    Camera::Camera(Position _eye, Position _centre, vector _up/*,rt::Scene* par*/) : eye(_eye), centre(_centre), up(_up)
    {
		//parent = par;
    }

    void Camera::generate(int height, int width)
    {
        
    }

}
