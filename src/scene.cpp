#include "scene.h"

namespace rt
{
    Scene::Scene()
    {

    }

    void Scene::render(screen& s)
    {

      vector up = cam->getUp() ;
      Position centre = cam->getCentre();
      Position eye = cam->getEye();
      vector _up = up.unit();
      vector vcenter = vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ());
      vector right = vcenter.unit() ^ _up;
      for(int i = 0; i < s.width(); ++i)
        {
		  for(int j = 0; j < s.height(); ++j)
		        {

				  bool inter = false;
				  rt::color c;
				  for(int k = 0; k < objets.size(); k++)
				        {
						  if(objets[k]->intersect(eye, vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up))
						  {
							inter = true;
							c = objets[k]->getTexture().getColor();
						  }
				        }
				  if(inter)
				  {
                    s.set_pixel(i, j, c);
				  }
				  else
                    s.set_pixel(i, j, color::WHITE);
		        }
		    }
		    printf("Finished\n");
 	}


    void Scene::addMesh(Mesh* mesh)
    {
		objets.push_back(mesh);
    }

    void Scene::addLight(const Light* light)
    {

    }

    void Scene::setCamera(Camera* camera)
    {
		cam = camera;
    }

}
