#include "sphere.h"

namespace rt
{
    Sphere::Sphere(int _centre, int _rayon)
    {
        centre = _centre;
        rayon = _rayon;
    }
    
    bool Sphere::intersect(Camera& camera)
    {
        return false;
    }
}
