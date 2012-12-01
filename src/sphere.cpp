#include "sphere.h"

namespace rt
{
  Sphere::Sphere(Position c, double r, Texture text) : Mesh(text), centre(c), radius(r)
    {
    }


    bool Sphere::intersect(const Position& point, const vector& vect)
    {
        double delta = (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        * (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
        * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX()) + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY()) + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ()) - radius * radius);
        //Calcul du discriminant
        if( delta > 0)
        {
            if(-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) - std::sqrt(delta) > 0)
                return true;
        }
        return false;
    }

    Position Sphere::getIntersection(const Position& point, const vector& vect)
    {
        double delta = (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        * (vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))
        - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
        * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX()) + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY()) + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ()) - radius * radius);
        //Calcul du discriminant
        double t = (-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) - std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);

        return Position(point.getX() + t * vect.x, point.getY() + t * vect.y, point.getZ() + t * vect.z);
    }

}
