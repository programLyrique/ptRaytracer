#include "camera.h"

Camera::Camera(Position eye, Position centre, vector up)
{
    Camera::eye = eye;
    Camera::centre = centre;
    Camera::up = up;
}
