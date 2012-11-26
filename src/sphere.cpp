#include "sphere.h"

namespace rt
{
    Sphere::Sphere(Position centre, double radius)
    {
        Sphere::centre = centre;
        Sphere::radius = radius;
    }

    bool Sphere::intersect(const Position& point, const vector& vect)
    {
        return false;
    }
}
