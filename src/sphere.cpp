#include "sphere.h"

namespace rt
{
Sphere::Sphere() : radius(10)
{

}

Sphere::Sphere(Point c, double r, Texture text) : Solid(text), centre(c), radius(r)
{

}


bool Sphere::intersect(const Point& point, const vector& vect) const
{
    //Calcul du discriminant
    double delta = (vect.x * (Sphere::centre.getX() - point.getX())
                    + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ()))
                   * (vect.x * (Sphere::centre.getX() - point.getX())
                      + vect.y * (Sphere::centre.getY() - point.getY())
                      + vect.z * (Sphere::centre.getZ() - point.getZ()))
                   - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
                   * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX())
                      + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY())
                      + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ())
                      - radius * radius);

    if(delta > 0)
    {
        if(-((vect.x * (Sphere::centre.getX() - point.getX())
                + vect.y * (Sphere::centre.getY() - point.getY())
                + vect.z * (Sphere::centre.getZ() - point.getZ())))
                - std::sqrt(delta) < 0
                || (-((vect.x * (Sphere::centre.getX() - point.getX())
                       + vect.y * (Sphere::centre.getY() - point.getY())
                       + vect.z * (Sphere::centre.getZ() - point.getZ())))
                    + std::sqrt(delta)) < 0)
            return true;
    }
    return false;
}

Point Sphere::getIntersection(const Point& point, const vector& vect) const
{
    //Re-calcul du discriminant
    double delta = (vect.x * (Sphere::centre.getX() - point.getX())
                    + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ()))
                   * (vect.x * (Sphere::centre.getX() - point.getX())
                      + vect.y * (Sphere::centre.getY() - point.getY())
                      + vect.z * (Sphere::centre.getZ() - point.getZ()))
                   - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
                   * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX())
                      + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY())
                      + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ())
                      - radius * radius);

    double t1 = (-((vect.x * (Sphere::centre.getX() - point.getX())
                    + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ())))
                 - std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
    double t2 = (-((vect.x * (Sphere::centre.getX() - point.getX())
                    + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ())))
                 + std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
    Point p1(point.getX() - t1 * vect.x, point.getY() - t1 * vect.y, point.getZ() - t1 * vect.z);
    Point p2(point.getX() - t2 * vect.x, point.getY() - t2 * vect.y, point.getZ() - t2 * vect.z);

    if(p1.distance(point) < p2.distance(point))
        return p1;
    else
        return p2;
}

Point Sphere::autreCote(const Point& point, const vector& vect, const Point& act) const
{
    //Et re-calcul du discriminant
    double delta = (vect.x * (Sphere::centre.getX() - point.getX())
                    + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ()))
                   * (vect.x * (Sphere::centre.getX() - point.getX())
                      + vect.y * (Sphere::centre.getY() - point.getY())
                      + vect.z * (Sphere::centre.getZ() - point.getZ()))
                   - (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z)
                   * ((Sphere::centre.getX() - point.getX()) * (Sphere::centre.getX() - point.getX())
                      + (Sphere::centre.getY() - point.getY()) * (Sphere::centre.getY() - point.getY())
                      + (Sphere::centre.getZ() - point.getZ()) * (Sphere::centre.getZ() - point.getZ())
                      - radius * radius);

    double t1 = (-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ()))) - std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
    double t2 = (-((vect.x * (Sphere::centre.getX() - point.getX()) + vect.y * (Sphere::centre.getY() - point.getY())
                    + vect.z * (Sphere::centre.getZ() - point.getZ()))) + std::sqrt(delta)) / (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
    Point p1(point.getX() - t1 * vect.x, point.getY() - t1 * vect.y, point.getZ() - t1 * vect.z);
    Point p2(point.getX() - t2 * vect.x, point.getY() - t2 * vect.y, point.getZ() - t2 * vect.z);

    if(p1 != act)
        return p1;
    else
        return p2;
}

vector Sphere::getNormal(const Point& p, const vector& vect) const
{
    return centre.vectTo(p).unit();
}

}
