#include "scene.h"

#include <cmath>
#include <iostream>

namespace rt
{
    Scene::Scene()
    {

    }

    void Scene::renderArea(unsigned x, unsigned y, unsigned width, unsigned height, screen& s)
    {
        std::cout << "Rendering of " << x << "," << y << " - " << width << "," << height << std::endl;
        vector up = cam->getUp() ;
        Position centre = cam->getCentre();
        Position eye = cam->getEye();
        vector _up = up.unit();
        vector vcenter = vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ());
        vector right = vcenter.unit() ^ _up;
        // Rendering of the rectangle.
        for(unsigned i = x; i < width; ++i)
        {
		  for(unsigned j = y; j < height; ++j)
		        {

				  bool inter = false;
				  rt::color c;
				  for(unsigned k = 0; k < objets.size(); k++)
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
				  //else
                  //  s.set_pixel(i, j, color::WHITE); // Black is the background.
		        }
        }
        //s.fill_rect(x,y,width, height, color::BLUE);
    }

    /*unsigned b_log(unsigned i)
    {
        i |= (i >> 1); i |= (i >> 2); i |= (i >> 4); i |= (i >> 8); i |= (i >> 16);
        return i - (i >>> 1);
    }*/

    void Scene::render(screen& s, unsigned nbThreads)
    {
        std::cout << "Rendering with " << nbThreads << std::endl;
        // Most of the times, the number of procs is a power of 2.
        // Anyway, it's rarely a prime number (except 2...).
        unsigned p2 = std::log(nbThreads) / std::log(2);//More efficient to detect the most significant bit
        unsigned nb_w = 0; // Nombre de divisions de la largeur
        unsigned nb_h = 0; // Nombre de morceaux en hauteur
        //What is the longest side ?
        if(s.height() > s.width())
        {
            nb_w = std::pow(2, p2 / 2);
            nb_h = nbThreads / nb_w ;
        }
        else
        {
            nb_h = std::pow(2, p2 / 2);
            nb_w = nbThreads / nb_h ;
        }

        unsigned w = s.width() / nb_w;
        unsigned h = s.height() / nb_h;
        std::cout << "Parts are " << w << " x " << h << std::endl;
        std::cout << "There are " << nb_w << " parts in width and " << nb_h << " in height." << std::endl;
        unsigned limit_w = w * (nb_w - 1);
        unsigned limit_h = h * (nb_h - 1 );
        std::cout << "Number of simple parts : limit_w = " << limit_w << " and limit_h = " << limit_h << std::endl;
        for(int i = 0 ; i <  s.width(); i += w)
            for(int j = 0; j < s.height(); j += h)
            {
                std::cout << "Rendering area (" << i << "," << j << ")" << std::endl;
                renderArea(i,j,w,h,s);
            }
        //Render the last parts (w,h + reminder of the devision)
        /*std::cout << "Rendering last parts" << std::endl;
        for(unsigned i = 0; i < limit_w ; i += w)
            renderArea(i, limit_h, w, s.height() - h, s);
        for(unsigned j=0; j < limit_h; j += h)
            renderArea(limit_w, j, s.width() - h, h, s);
        std::cout << "End of rendering" << std::endl;*/
 	}

    void Scene::render(screen& s)
    {
        render(s, Thread::nbCores());
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
