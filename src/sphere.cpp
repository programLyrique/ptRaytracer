#include "sphere.h"

namespace rt
{
  Sphere::Sphere(Position c, double r, Texture text) : Mesh(text), centre(c), radius(r)
    {
    }


    bool Sphere::intersect(const Position& point, const vector& vect)
    {
        //Calcul du discriminant
        return (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        * (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
        * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX()) + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY()) + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ()) - radius * radius)
        > 0;
    }

}
