#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, double pow) : Position(x, y, z), Light(pow)
    {
     
    }
    
    double PointLight::illuminate(const Position& p)
    {
    	return 0.;
    }
}
