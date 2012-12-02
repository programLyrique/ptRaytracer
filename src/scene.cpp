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
				  int o = 0;
				  vector v = (vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up).unit();
				  for(unsigned k = 0; k < objets.size(); k++)
                  {
					  if(objets[k]->intersect(eye, v))
					  {

						rt::Position pos = objets[k]->getIntersection(eye, v);
						if(inter)
						{
                            if(eye.distance(pos) < eye.distance(p))
                            {
                               c = objets[k]->getTexture().getColor();
                               p = pos;
                               o = k;
                            }

						}
						else
						{
						    inter = true;
						    p = pos;
						    c = objets[k]->getTexture().getColor();
						    o = k;
						}
						//printf("%f %f %f ", p.getX(), p.getY(), p.getZ());
                       }
                  }

				  if(inter)
				  {
				  	vector tem = (-1 * v).unit();
				  	double l1 = lampes[0]->illuminateB(p, (Sphere*) objets[o], tem);
				  	double l2 = lampes[0]->illuminateR(p, (Sphere*) objets[o], tem);
				  	double l3 = lampes[0]->illuminateG(p, (Sphere*) objets[o], tem);
				  	//printf("%d %d %d\n", l1, l2, l3);
                    s.set_pixel(i, j, color(255 * l2, 255 * l3, 255 * l1));
                    //printf("%f %f %f %d %d", tem.x, tem.y, tem.z, i, j);
                    //printf("\n");
				  }
				  //else
                  //  s.set_pixel(i, j, color::BLACK);

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
