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
      printf("%f %f %f, %f %f %f\n", centre.getX(), centre.getY(), centre.getZ(), eye.getX(), eye.getY(), eye.getZ());
      vector right = vcenter.unit() ^ _up;
      printf("Starting: %d %d\n", objets.size(), lampes.size());
      for(int i = 0; i < s.width(); ++i)
        {
		  for(int j = 0; j < s.height(); ++j)
		        {
		          
				  bool inter = false;
				  for(int k = 0; k < objets.size(); k++)
				        {
				        	//rt::vector vect = vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up;
				        	//printf("vect %d %d %d \n", vcenter.x, vcenter.y, vcenter.z);
						  if(objets[k]->intersect(eye, vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up))
						  {
							inter = true;
							printf("Found\n");
						  }
				        }
				  if(inter)
				s.set_pixel(i, j, color::BLACK);
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
