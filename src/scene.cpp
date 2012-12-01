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
				  rt::Position p;
				  for(unsigned k = 0; k < objets.size(); k++)
                  {
					  if(objets[k]->intersect(eye, vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up))
					  {

						rt::Position pos = objets[k]->getIntersection(eye, vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up);
						if(inter)
						{
                            if(eye.distance(pos) < eye.distance(p))
                            {
                               c = objets[k]->getTexture().getColor();
                               p = pos;
                            }

						}
						else
						{
						    inter = true;
						    p = pos;
						    c = objets[k]->getTexture().getColor();
						}
						printf("%f %f %f\n", p.getX(), p.getY(), p.getZ());
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

    void Scene::addLight(Light* light)
    {
		lampes.push_back(light);
    }

    void Scene::setCamera(Camera* camera)
    {
		cam = camera;
    }

}
