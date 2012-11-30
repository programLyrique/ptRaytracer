#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, double pow, Scene* parent) : Position(x, y, z), Light(pow, parent)
    {

    }

    int PointLight::illuminateR(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;

    	for(const_iterator it = parent->getDebObjets(); it != parent.getFinObjets(); ++it)
    	{
    	    if(it->intersect(p, p.vectTo(*this)))
    	    {
    	        cache = true;
    	    }
    	}

    	if(!cache)
    	{
            return m->getTexture().getKaR() * (m->getCentre().vectTo(p).unit() | p.vectTo(*this)) + 2 * m->getTexture().getKsR() * vision | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this)) * m->getCentre().vectTo(p).unit() - p.vectTo(*this));
    	}

    	return 0;

    }

    int PointLight::illuminateG(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;

    	for(const_iterator it = parent->getDebObjets(); it != parent.getFinObjets(); ++it)
    	{
    	    if(it->intersect(p, p.vectTo(*this)))
    	    {
    	        cache = true;
    	    }
    	}

    	if(!cache)
    	{
            return m->getTexture().getKaG() * (m->getCentre().vectTo(p).unit() | p.vectTo(*this)) + 2 * m->getTexture().getKsG() * vision | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this)) * m->getCentre().vectTo(p).unit() - p.vectTo(*this));
    	}

    	return 0;

    }


    int PointLight::illuminateB(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;

    	for(const_iterator it = parent->getDebObjets(); it != parent.getFinObjets(); ++it)
    	{
    	    if(it->intersect(p, p.vectTo(*this)))
    	    {
    	        cache = true;
    	    }
    	}

    	if(!cache)
    	{
            return m->getTexture().getKaB() * (m->getCentre().vectTo(p).unit() | p.vectTo(*this)) + 2 * m->getTexture().getKsB() * vision | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this)) * m->getCentre().vectTo(p).unit() - p.vectTo(*this));
    	}

    	return 0;

    }
}
