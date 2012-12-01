#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, double powD, double powS, Scene* scene) : Light(powD, powS, scene), Position(x, y, z)
    {

    }

    int PointLight::illuminateR(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;
		int o = 0;
		int i = 0;
    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(p, p.vectTo(*this)))
    	    {
    	    	Position q = (*it)->getIntersection(p, p.vectTo(*this));
    	    	if((p.getX() - q.getX() > 0.0001)||(p.getY() - q.getY() > 0.0001)||(p.getZ() - q.getZ() > 0.0001))
    	    	{
    	        	cache = true;
    	        	o = i;
    	        }
    	    }
    	    ++i;
    	}

    	if(!cache)
    	{
            return ((double) m->getTexture().getColor().get_red() / ((double) 255) * m->getTexture().getKaR()) * (m->getCentre().vectTo(p).unit() | p.vectTo(*this)) + 2 * ((double) m->getTexture().getColor().get_red() / ((double) 255)) * m->getTexture().getKsR() * std::pow(vision | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this)) * m->getCentre().vectTo(p).unit() - p.vectTo(*this)), m->getTexture().getBrillance());
    	}
		/*else
			printf("Je suis cache par %d\n", o);*/
    	return 0;

    }
    
    int PointLight::illuminateG(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;
        int o = 0;
        int i = 0;

    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(p, p.vectTo(*this)))
    	    {
    	    	Position q = (*it)->getIntersection(p, p.vectTo(*this));
    	        if((p.getX() - q.getX() > 0.0001)||(p.getY() - q.getY() > 0.0001)||(p.getZ() - q.getZ() > 0.0001))
    	    	{
    	        	cache = true;
    	        	o = i;
    	        	printf("HIDDEN\n");
    	        	//printf("---------------------------------------\n");
    	        	//q.print();
    	        	//p.print();
    	        }
    	        
    	    }
    	    ++i;
    	}

    	if(!cache)
    	{
            return ((double) m->getTexture().getColor().get_green() / ((double) 255) * m->getTexture().getKaG()) * (m->getCentre().vectTo(p).unit() | p.vectTo(*this)) + 2 * ((double) m->getTexture().getColor().get_green() / ((double) 255)) * m->getTexture().getKsG() * std::pow(vision | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this)) * m->getCentre().vectTo(p).unit() - p.vectTo(*this)), m->getTexture().getBrillance());
    	}
		/*else
			printf("Je suis cache par %d\n", o);*/
    	return 0;

    }
    
    int PointLight::illuminateB(const Position& p, const Sphere* m, const vector vision)
    {
        bool cache = false;
		int o = 0;
		int i = 0;
    	for(std::vector<Mesh*>::const_iterator it = scene->getDebObjets(); it != scene->getFinObjets(); ++it)
    	{
    	    if((*it)->intersect(p, p.vectTo(*this)))
    	    {
    	    	Position q = (*it)->getIntersection(p, p.vectTo(*this));
    	        if((p.getX() - q.getX() > 0.0001)||(p.getY() - q.getY() > 0.0001)||(p.getZ() - q.getZ() > 0.0001))
    	    	{
    	        	cache = true;
    	        	o = i;
    	        }
    	    }
    	    ++i;
    	}

    	if(!cache)
    	{
            return ((double) m->getTexture().getColor().get_blue() / ((double) 255) * m->getTexture().getKaB()) * (m->getCentre().vectTo(p).unit() | p.vectTo(*this)) + 2 * ((double) m->getTexture().getColor().get_blue() / ((double) 255)) * m->getTexture().getKsB() * std::pow(vision | ((m->getCentre().vectTo(p).unit() | p.vectTo(*this)) * m->getCentre().vectTo(p).unit() - p.vectTo(*this)), m->getTexture().getBrillance());
    	}
    	/*else
			printf("Je suis cache par %d\n", o);*/

    	return 0;

    }

}
