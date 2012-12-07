#include "scene.h"
#include "thread.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include "screen.hpp"

namespace rt
{
    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::renderArea(int x, int y, int width, int height, screen& s, bool oversampling = true)
    {
        vector up = cam->getUp() ;
        Point centre = cam->getCentre();
        Point eye = cam->getEye();
        vector _up = up.unit();
        vector vcenter = vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ());
        vector right = vcenter.unit() ^ _up;
        // Rendering of the rectangle.
        for(int i = x; i < x + width; ++i)
        {
            for(int j = y; j < y + height; ++j)
            {
                double step = 0;
                double mL1 = 0;
                double mL2 = 0;
                double mL3 = 0;
                // Oversampling x 9
                if(oversampling)
                    step = 0.25;

                for(double ho=i - step; ho <= i + step ; ho += step)
                    for(double ve=j-step; ve <= j + step ; ve+=step)
                    {
                        if(not oversampling)
                        {
                            ho++;//eviter une boucle infinie
                            ve++;
                        }
                        //  std::cout  << ho << " et " << ve << std::endl;
                        bool inter = false;
                        Point p;
                        int o = 0;
                        vector v = (vcenter + (ho - s.width() / 2.0) * right + (ve - s.height() / 2.0) * _up).unit();
                        for(unsigned k = 0; k < objets.size(); k++)
                        {
                            if(objets[k]->intersect(eye, v))
                            {
                                Point pos = objets[k]->getIntersection(eye, v);
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
                            color temp = getIllumination(p, objets[o], v, 5, 5);
                            mL1 += temp.get_red();
                            mL2 += temp.get_green();
                            mL3 += temp.get_blue();
                        }
                    }
                if(oversampling)
                {
                    mL1 /= 9.0;
                    mL2 /= 9.0;
                    mL3 /= 9.0;
                }

                s.set_pixel(i, j, color((int)mL1, (int)mL2, (int)mL3));
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
        std::cout << "Rendering with " << nbThreads <<  " threads." << std::endl;

        std::cout << getNbObjects() << " objects. " << getNbLights() << " lights." << std::endl;
        // Most of the times, the number of procs is a power of 2.
        // Anyway, it's rarely a prime number (except 2...).
        int p2 = std::log(nbThreads) / std::log(2);//More efficient to detect the most significant bit
        int nb_w = 0; // Nombre de divisions de la largeur
        int nb_h = 0; // Nombre de morceaux en hauteur
        std::vector<ThreadRender*> threads(nbThreads);//A "pool" of threads
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

        time_t beginning = std::time(NULL);

        //int limit_w = w * (nb_w - 1); // useful when there are parts left by the divisions above.
        //int limit_h = h * (nb_h - 1 );
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
        for(k=0; k < nbThreads ; k++)
        {
            std::cout << "Launching thread n." << k + 1<< std::endl;
            threads[k]->exec();
        }
        s.update();
        for(k=0; k < nbThreads; k++)
        {
            threads[k]->join();
            s.update();//Probably useless
        }

        for(k=0; k < nbThreads; k++)
            delete threads[k];
        //Render the last parts (w,h + reminder of the devision)
        /*std::cout << "Rendering last parts" << std::endl;
        for(unsigned i = 0; i < limit_w ; i += w)
            renderArea(i, limit_h, w, s.height() - h, s);
        for(unsigned j=0; j < limit_h; j += h)
            renderArea(limit_w, j, s.width() - h, h, s);*/

        time_t end = std::time(NULL);
        std::cout << "End of rendering. Took " << end - beginning << " seconds." << std::endl;
    }

    void Scene::render(screen& s)
    {
        render(s, Thread::nbCores());
    }

    void Scene::addSolid(Solid* solid)
    {
        objets.push_back(solid);
    }

    void Scene::addLight(Light* light)
    {
        lights.push_back(light);
    }

    void Scene::setCamera(Camera* camera)
    {
        cam = camera;
    }
	/*
    bool Scene::existInterBetween(const Point& begin, const Point& end) const
    {
        vector v = begin.vectTo(end);
        for(std::vector<Solid*>::const_iterator it = objets.begin(); it != objets.end(); ++it)
    	{
    	    if((*it)->intersect(begin, v))
    	    {
    	    	Point q = (*it)->getIntersection(begin, v);
    	    	if((q.distance(begin) < end.distance(begin)) && (end != q))
    	    	{
    	        	return true;
    	        }
    	    }
    	}
    	return false;
    }
	*/
    color Scene::getIllumination(const Point& p, Solid* o, const vector& vect, int nbR, int nbTrans) const
    {
        vector v = vect;
        vector tem = (-1 * v).unit();
        color phong;
        color reflechie;
        color transparenceObjet;

        for(unsigned k = 0; k < lights.size(); ++k)
        {
            color temp = lights[k]->illuminate(p, o, tem);
            phong.set_red(std::min(temp.get_red() + phong.get_red(), 255));
            phong.set_green(std::min(temp.get_green() + phong.get_green(), 255));
            phong.set_blue(std::min(temp.get_blue() + phong.get_blue(), 255));
        }
        vector reflection = (2 * (tem | o->getNormal(p, v)) * o->getNormal(p, v) - tem).unit();
        bool reflect = false;
        Point brill;
        int e = 0;

        for(unsigned k = 0; k < objets.size(); k++)
        {
            if(objets[k]->intersect(p, reflection))
            {
                Point pos = objets[k]->getIntersection(p, reflection);
                if(objets[k] != o)
                {
                    if(reflect)
                    {
                        if(p.distance(pos) < p.distance(brill))
                        {

                            brill = pos;
                            e = k;
                        }
                    }
                    else
                    {
                        reflect = true;
                        brill = pos;
                        e = k;
                    }
                }
            }
        }
        if(nbR > 0)
        {
            if(reflect)
            {
            	color cB = o->getTexture().getColorB();
                color temp = getIllumination(brill, objets[e], reflection, nbR - 1, nbTrans);
                reflechie.set_red(std::min((int) ((cB.get_red() / 255.) * (reflechie.get_red() + temp.get_red())), 255));
                reflechie.set_green(std::min((int) ((cB.get_green() / 255.) * (reflechie.get_green() + temp.get_green())), 255));
                reflechie.set_blue(std::min((int) ((cB.get_red() / 255.) * (reflechie.get_blue() + temp.get_blue())), 255));
            }
        }
        if(nbTrans > 0)
        {
            double n1n2 = 1/(o->getTexture().getIndice());
            v = v.unit();
            vector normal = o->getNormal(p, v).unit();
            vector r =  (n1n2 * v - (- n1n2 * (v | normal) - std::sqrt(1 - n1n2 * n1n2 * (1 - (v | normal) *(v | normal)))) * normal).unit();
            Point transp(o->autreCote(p, r, p));
            vector normal2 = o->getNormal(transp, r).unit();
            tem = (n1n2 * r - (n1n2 * (r | normal2) - std::sqrt(1 - n1n2 * n1n2 * (1 - (r | normal2) *(r | normal2)))) * normal2).unit();

            if(o->getTexture().getTransparence() != 0)
            {
                bool brillance = false;
                for(unsigned k = 0; k < objets.size(); k++)
                {
                    if(objets[k]->intersect(transp, tem))
                    {
                        Point pos = objets[k]->getIntersection(transp, tem);
                        if(objets[k] != o)
                        {
                            if(brillance)
                            {
                                if(transp.distance(pos) < transp.distance(brill))
                                {
                                   brill = pos;
                                   e = k;
                                }
                            }
                            else
                            {
                                brillance = true;
                                brill = pos;
                                e = k;
                            }
                        }

                    }
                }
                if(brillance)
                {
                    color temp = getIllumination(brill, objets[e], tem, nbR, nbTrans - 1);
                    transparenceObjet.set_red(std::min(transparenceObjet.get_red()
                                                         + ((double) objets[e]->getTexture().getColorN().get_red() / 255.)
                                                            * temp.get_red()
                                                       , 255.));
                    transparenceObjet.set_green(std::min(transparenceObjet.get_green()
                                                         + ((double) objets[e]->getTexture().getColorN().get_green() / 255.)
                                                            * temp.get_green()
                                                       , 255.));
                    transparenceObjet.set_blue(std::min(transparenceObjet.get_blue()
                                                         + ((double) objets[e]->getTexture().getColorN().get_blue() / 255.)
                                                            * temp.get_blue()
                                                       , 255.));
                }
            }
        }
        double t = o->getTexture().getTransparence();
        return color(std::min(((1 - t) * phong.get_red()
                               + (1 - t) * reflechie.get_red()
                               + t * transparenceObjet.get_red()), 255.),
                     std::min(((1 - t) * phong.get_green()
                               + (1 - t) * reflechie.get_green()
                               + t * transparenceObjet.get_green()), 255.),
                     std::min(((1 - t) * phong.get_blue()
                               + (1 - t) * reflechie.get_blue()
                               + t * transparenceObjet.get_blue()), 255.));
    }

    double Scene::existInterBetween(const Point& begin, const Point& end) const
    {
    	double t = 1;
        vector v = begin.vectTo(end);
        for(std::vector<Solid*>::const_iterator it = objets.begin(); it != objets.end(); ++it)
    	{
    	    if((*it)->intersect(begin, v))
    	    {
    	    	Point q = (*it)->getIntersection(begin, v);
    	    	if((q.distance(begin) < end.distance(begin)) && (end != q))
    	    	{
    	    		double te = (*it)->getTexture().getTransparence();
    	    		if(0. == te)
    	    			return 0.;
    	        	t *= te;
    	        }
    	    }
    	}
    	return t;
    }

}
