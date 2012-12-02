#include "scene.h"

#include <cmath>
#include <iostream>

namespace rt
{
    Scene::Scene()
    {

    }

    void Scene::renderArea(int x, int y, int width, int height, screen& s)
    {
        vector up = cam->getUp() ;
        Position centre = cam->getCentre();
        Position eye = cam->getEye();
        vector _up = up.unit();
        vector vcenter = vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ());
        vector right = vcenter.unit() ^ _up;
        // Rendering of the rectangle.
        for(int i = x; i < x + width; ++i)
        {
		  for(int j = y; j < y + height; ++j)
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
		        }
        }
    }

    Scene::ThreadRender::ThreadRender(Scene& _sc,int _x, int _y, int _w, int _h, screen& _s) :
        sc(_sc),x(_x), y(_y), w(_w), h(_h), s(_s)
    {

    }
    void Scene::ThreadRender::run()
    {
        sc.renderArea(x,y,w,h,s);
    }

    void Scene::render(screen& s, int nbThreads)
    {
        std::cout << "Rendering with " << nbThreads << std::endl;
        // Most of the times, the number of procs is a power of 2.
        // Anyway, it's rarely a prime number (except 2...).
        int p2 = std::log(nbThreads) / std::log(2);//More efficient to detect the most significant bit
        int nb_w = 0; // Nombre de divisions de la largeur
        int nb_h = 0; // Nombre de morceaux en hauteur
        std::vector<Thread*> threads(nbThreads);
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

        int w = s.width() / nb_w;
        int h = s.height() / nb_h;
        std::cout << "Parts are " << w << " x " << h << std::endl;
        std::cout << "There are " << nb_w << " parts in width and " << nb_h << " in height." << std::endl;
        int limit_w = w * (nb_w - 1);
        int limit_h = h * (nb_h - 1 );
        int k = 0;
        //std::cout << "Number of simple parts : limit_w = " << limit_w << " and limit_h = " << limit_h << std::endl;
        for(int i = 0 ; i <  s.width(); i += w)
            for(int j = 0; j < s.height(); j += h)
            {
                std::cout << "Rendering of " << i << "," << j << " - " << w << "," << h << std::endl;
                threads[k] = new ThreadRender(*this,i,j,w,h,s);
                //renderArea(i,j,w ,h,s);
                k++;
            }
        for(k=0; k < nbThreads ;k++)
            threads[k]->exec();
        for(k=0;k < nbThreads; k++)
            threads[k]->join();
        for(k=0; k < nbThreads;k++)
            delete threads[k];
        //Render the last parts (w,h + reminder of the devision)
        /*std::cout << "Rendering last parts" << std::endl;
        for(unsigned i = 0; i < limit_w ; i += w)
            renderArea(i, limit_h, w, s.height() - h, s);
        for(unsigned j=0; j < limit_h; j += h)
            renderArea(limit_w, j, s.width() - h, h, s);*/
        std::cout << "End of rendering" << std::endl;
 	}

    void Scene::render(screen& s)
    {
        render(s, Thread::nbCores());
        //renderArea(0,0, s.width() , s.height(),s);//To debug
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
