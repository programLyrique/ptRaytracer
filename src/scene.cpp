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
        delete cam;
        for(std::vector<Solid*>::iterator it = objets.begin(); it != objets.end(); ++it)
        {
            delete (*it);
        }
        
        for(std::vector<Light*>::iterator it = lights.begin(); it != lights.end(); ++it)
        {
            delete (*it);
        }
    }

    void Scene::render(screen& s)
    {
        vector up = cam->getUp() ;
        Point centre = cam->getCentre();
        Point eye = cam->getEye();
        vector _up = up.unit();
        vector vcenter = vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ());
        vector right = vcenter.unit() ^ _up;
        // Rendering of the rectangle.
        for(int i = 0; i < s.width(); ++i)
        {
            for(int j = 0; j < s.height(); ++j)
            {

            	bool inter = false;
                Point p;
                int o = 0;
                int r = 0;
                int g = 0;
                int b = 0;
             	vector v = (vcenter + (i - s.width() / 2.0) * right + (j - s.height() / 2.0) * _up).unit();
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
                	color temp = getIllumination(p, objets[o], v);
                	r = temp.get_red();
                	g = temp.get_green();
                	b = temp.get_blue();
                }
                s.set_pixel(i, j, color(r, g, b));
            }
        }
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
	
    color Scene::getIllumination(const Point& p, Solid* o, const vector& vect) const
    {
        vector tem = (-1 * vect).unit();
        color phong;

        for(unsigned k = 0; k < lights.size(); ++k)
        {
            color temp = lights[k]->illuminate(p, o, tem);
            phong.set_red(std::min(temp.get_red() + phong.get_red(), 255));
            phong.set_green(std::min(temp.get_green() + phong.get_green(), 255));
            phong.set_blue(std::min(temp.get_blue() + phong.get_blue(), 255));
        }
        
        return phong;
    }

}
