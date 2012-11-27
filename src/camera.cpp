#include "camera.h"

Camera::Camera(Position _eye, Position _centre, vector up, Scene& par) eye(_eye), centre(_centre)
{
    parent = par
    Camera::up = up;
}

void Camera::generate(int height, int width)
{
    rt::vector _up = up.norm();
    rt::vector vcenter = rt::vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ())
    rt::vector right = vcenter.norm()^_up;

    image im(width, height);

    for(int i = 0; i < width; ++i)
    {
        for(int j = 0; j < height; ++j)
        {
            bool inter = false;
            for(int k = 0; k < parent.getObjets.size(); k++)
            {
                if(parent.getObjets()[k].intersect(eye, vcenter + (i - width / 2) * right + (j - height / 2) * _up))
                    inter = true;
            }
            if(inter)
                im.set_pixel(i, j, color::BLACK);
            else
                im.set_pixel(i, j, color::WHITE);
        }
    }
}


