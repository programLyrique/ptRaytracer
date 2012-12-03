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
            if(-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) - std::sqrt(delta) < 0 || (-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) + std::sqrt(delta)) < 0)
            	//printf("%f\n", -((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) - std::sqrt(delta));
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
        double t1 = (-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) - std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
        double t2 = (-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY()) + vect.z * (Sphere::centre.getZ() - point.getZ()))) + std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
        Position p1(point.getX() - t1 * vect.x, point.getY() - t1 * vect.y, point.getZ() - t1 * vect.z);
        Position p2(point.getX() - t2 * vect.x, point.getY() - t2 * vect.y, point.getZ() - t2 * vect.z);
        //printf("---------------\n");
        //p1.print();
        //p2.print();
        
        if(p1.distance(point) < p2.distance(point))
        	return p1;
		else
        	return p2;
    }
    
    vector Sphere::getNormal(const Position& p, const vector& vect) const
    {
    	return centre.vectTo(p);
    }

}
