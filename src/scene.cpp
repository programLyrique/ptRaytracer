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
                               p = pos;
                               o = k;
                            }

						}
						else
						{
						    inter = true;
						    p = pos;
						    o = k;
						}
                       }
                  }

				  if(inter)
				  {
				  	vector tem = (-1 * v).unit();
				  	double l1 = 0; 
				  	double l2 = 0; 
				  	double l3 = 0; 
				  	
				  	for(int k = 0; k < lampes.size(); ++k)
				  	{
				  		l1 += lampes[k]->illuminateR(p, (Sphere*) objets[o], tem);
				  		l2 += lampes[k]->illuminateG(p, (Sphere*) objets[o], tem);				  		
				  		l3 += lampes[k]->illuminateB(p, (Sphere*) objets[o], tem);				  		
				  	}
				  	
				  	l1 = std::min(l1, 255.);
				  	l2 = std::min(l2, 255.);
				  	l3 = std::min(l3, 255.);
				  	
                    s.set_pixel(i, j, color((int)l1, (int)l2, (int)l3));
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
