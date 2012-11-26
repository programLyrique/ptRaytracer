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

    bool Sphere::intersect(Position& point, vector& vect)
    {
        return (vect.x * (centre.getX() - point.getX()) + vect.y * (centre.getY() - point.getY()) + vect.z * (centre.getZ() - point.getZ()))
        * (vect.x * (centre.getX() - point.getX()) + vect.y * (centre.getY() - point.getY()) + vect.z * (centre.getZ() - point.getZ()))
        - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
        * ((centre.getX() - point.getX()) * (centre.getX() - point.getX()) + (centre.getY() - point.getY()) * (centre.getY() - point.getY()) + (centre.getZ() - point.getZ()) * (centre.getZ() - point.getZ()) - rayon * rayon)
        > 0;
    }
}
