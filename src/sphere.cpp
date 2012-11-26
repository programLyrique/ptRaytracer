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

    bool Sphere::intersect(Position& pos, vector& vect)
    {
        return (vect.x * (centre.getX() - pos.getX()) + vect.y * (centre.getY() - pos.getY()) + vect.z * (centre.getZ() - pos.getZ()))
        * (vect.x * (centre.getX() - pos.getX()) + vect.y * (centre.getY() - pos.getY()) + vect.z * (centre.getZ() - pos.getZ()))
        - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
        * ((centre.getX() - pos.getX()) * (centre.getX() - pos.getX()) + (centre.getY() - pos.getY()) * (centre.getY() - pos.getY()) + (centre.getZ() - pos.getZ()) * (centre.getZ() - pos.getZ()) - rayon * rayon)
        > 0;
    }
}
