#include "scene.h"

namespace rt
{
    Scene::Scene()
    {

    }

    void Scene::render(screen& s)
    {
	rt::vector _up = up.norm();
        rt::vector vcenter = rt::vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ())
        rt::vector right = vcenter.norm()^_up;

        for(int i = 0; i < s.width(); ++i)
        {
            for(int j = 0; j < s.height(); ++j)
            {
                bool inter = false;
                for(int k = 0; k < objets.size(); k++)
                {
                    if(objets[k].intersect(eye, vcenter + (i - width / 2) * right + (j - height / 2) * _up))
                        inter = true;
                }
                if(inter)
                    s.set_pixel(i, j, color::BLACK);
                else
                    s.set_pixel(i, j, color::WHITE);
            }
        }
    }


    void addMesh(const Mesh* mesh)
    {

    }

    void addLight(const Light* light)
    {

    }

    void setCamera(const Camera* camera)
    {

    }

}
