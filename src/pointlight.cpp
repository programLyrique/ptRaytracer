#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, color c, Scene* scene) : Light(c, scene), Position(x, y, z)
    {

    }

    double PointLight::illuminateR(const Position& p, const Mesh* m, const vector vision)
    {
    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(*this, this->vectTo(p)))
    	    {
    	    	Position q = (*it)->getIntersection(*this, this->vectTo(p));
    	    	if((q.distance(*this) < p.distance(*this)) && ((std::abs(p.getX() - q.getX()) > 0.0001)||(std::abs(p.getY() - q.getY()) > 0.0001)||(std::abs(p.getZ() - q.getZ()) > 0.0001)))
    	    	{
    	        	return 0;
    	        }
    	    }
    	}

    	double a = std::max(0., ((double) m->getTexture().getColorN().get_red() / ((double) 255)) * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double b = std::max(0., ((double) m->getTexture().getColorB().get_red() / ((double) 255)) * std::pow(vision.unit() | (2 * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()).unit() - p.vectTo(*this).unit()).unit(), m->getTexture().getBrillance()));
         return std::min(couleur.get_red() * (a + b), 255.);

    }
    
    double PointLight::illuminateG(const Position& p, const Mesh* m, const vector vision)
    {

    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(*this, this->vectTo(p)))
    	    {
    	    	Position q = (*it)->getIntersection(*this, this->vectTo(p));
    	        if((q.distance(*this) < p.distance(*this)) && ((std::abs(p.getX() - q.getX()) > 0.0001)||(std::abs(p.getY() - q.getY()) > 0.0001)||(std::abs(p.getZ() - q.getZ()) > 0.0001)))
    	    	{
    	        	return 0;
    	        	
    	        }
    	        
    	    }
    	}

    	double a = std::max(0., ((double) m->getTexture().getColorN().get_green() / ((double) 255)) * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double b = std::max(0., ((double) m->getTexture().getColorB().get_green() / ((double) 255)) * std::pow(vision.unit() | (2 *(m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()).unit() - p.vectTo(*this).unit()).unit(), m->getTexture().getBrillance()));
        return std::min(couleur.get_green() * (a + b), 255.);

    }
    
    double PointLight::illuminateB(const Position& p, const Mesh* m, const vector vision)
    {
    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(*this, this->vectTo(p)))
    	    {
    	    	Position q = (*it)->getIntersection(*this, this->vectTo(p));

    	        if((q.distance(*this) < p.distance(*this)) && ((std::abs(p.getX() - q.getX()) > 0.0001)||(std::abs(p.getY() - q.getY()) > 0.0001)||(std::abs(p.getZ() - q.getZ()) > 0.0001)))
    	    	{
    	    		return 0;
    	        }
    	    }
    	}

    	double a = std::max(0., ((double) m->getTexture().getColorN().get_blue() / ((double) 255)) * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double b = std::max(0., ((double) m->getTexture().getColorB().get_blue() / ((double) 255)) * std::pow(vision.unit() | (2 * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()).unit() - p.vectTo(*this).unit()).unit(), m->getTexture().getBrillance()));
        return std::min(couleur.get_blue() * (a + b), 255.);

    }

}
