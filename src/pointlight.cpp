#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, double pow, Scene* parent) : Position(x, y, z), Light(pow, parent)
    {
     
    }
    
    double PointLight::illuminate(const Position& p)
    {
        double sortie = power;
    	for(const_iterator it = parent->getDebObjets(); it != parent.getFinObjets(); ++it)
    	{
    	    if(it->intersect(p, p.vectTo(*this)))
    	    {
    	        sortie = 0;
    	    }
    	}
    	
    	return (sortie / this->distance(p));
    	
    }
}
