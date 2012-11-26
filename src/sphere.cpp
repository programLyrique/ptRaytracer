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
        return (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        * (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
        * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX()) + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY()) + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ()) - rayon * rayon)
        > 0;
    }
}
