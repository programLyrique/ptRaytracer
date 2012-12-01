#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, double powD, double powS, Scene* scene) : Light(powD, powS, scene), Position(x, y, z)
    {

    }

    double PointLight::illuminateR(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;
		int o = 0;
		int i = 0;
    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(*this, this->vectTo(p)))
    	    {
    	    	Position q = (*it)->getIntersection(*this, this->vectTo(p));
    	    	if((p.getX() - q.getX() > 0.0001)||(p.getY() - q.getY() > 0.0001)||(p.getZ() - q.getZ() > 0.0001))
    	    	{
    	        	cache = true;
    	        	//printf("HIDDEN\n");
    	        	o = i;
    	        }
    	    }
    	    ++i;
    	}

    	if(!cache)
    	{
    		double a = std::max(0., ((double) m->getTexture().getColor().get_red() / ((double) 255) * m->getTexture().getKaR()) * (m->getCentre().vectTo(p).unit() | p.vectTo(*this).unit()));
    		double b = std::max(0., 2 * ((double) m->getTexture().getColor().get_red() / ((double) 255)) * m->getTexture().getKsR() * std::pow(vision.unit() | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this).unit()) * m->getCentre().vectTo(p).unit() - p.vectTo(*this).unit()).unit(), m->getTexture().getBrillance()));
    		if(a < 0 || b < 0) 
    			printf("rouge: %f %f ", a, b);
            return std::min(a + b, 255.);
    	}
		/*else
			printf("Je suis cache par %d\n", o);*/
    	return 0;

    }
    
    double PointLight::illuminateG(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;
        int o = 0;
        int i = 0;

    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(*this, this->vectTo(p)))
    	    {
    	    	Position q = (*it)->getIntersection(*this, this->vectTo(p));
    	        if((p.getX() - q.getX() > 0.0001)||(p.getY() - q.getY() > 0.0001)||(p.getZ() - q.getZ() > 0.0001))
    	    	{
    	        	cache = true;
    	        	o = i;
    	        	//printf("HIDDEN\n");
    	        	//printf("---------------------------------------\n");
    	        	//q.print();
    	        	//p.print();
    	        }
    	        
    	    }
    	    ++i;
    	}

    	if(!cache)
    	{
    		double a = std::max(0., ((double) m->getTexture().getColor().get_green() / ((double) 255) * m->getTexture().getKaG()) * (m->getCentre().vectTo(p).unit() | p.vectTo(*this).unit()));
    		double b = std::max(0., 2 * ((double) m->getTexture().getColor().get_green() / ((double) 255)) * m->getTexture().getKsG() * std::pow(vision.unit() | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this).unit()) * m->getCentre().vectTo(p).unit() - p.vectTo(*this).unit()).unit(), m->getTexture().getBrillance()));
    		if(a < 0 || b < 0) 
    			printf("vert: %f %f ", a, b);
            return  std::min(a + b, 255.);
    	}
		/*else
			printf("Je suis cache par %d\n", o);*/
    	return 0;

    }
    
    double PointLight::illuminateB(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;
		int o = 0;
		int i = 0;
    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(*this, this->vectTo(p)))
    	    {
    	    	Position q = (*it)->getIntersection(*this, this->vectTo(p));
    	        if((p.getX() - q.getX() > 0.0001)||(p.getY() - q.getY() > 0.0001)||(p.getZ() - q.getZ() > 0.0001))
    	    	{
    	        	cache = true;
    	        	//printf("HIDDEN\n");
    	        	o = i;
    	        }
    	    }
    	    ++i;
    	}

    	if(!cache)
    	{
    		double a = std::max(0., ((double) m->getTexture().getColor().get_blue() / ((double) 255) * m->getTexture().getKaB()) * (m->getCentre().vectTo(p).unit() | p.vectTo(*this).unit()));
    		double b = std::max(0., 2 * ((double) m->getTexture().getColor().get_blue() / ((double) 255)) * m->getTexture().getKsB() * std::pow(vision.unit() | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this).unit()) * m->getCentre().vectTo(p).unit() - p.vectTo(*this).unit()).unit(), m->getTexture().getBrillance()));
    		if(a < 0 || b < 0) 
    			printf("bleu: %f %f\n", a, b);
            return std::min(a + b, 255.);
    	}
    	/*else
			printf("Je suis cache par %d\n", o);*/

    	return 0;

    }

}
