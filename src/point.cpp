#include "point.h"

namespace rt
{
    Point::Point(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    double Point::getX() const
    {
        return x;
    }

    double Point::getY() const
    {
        return y;
    }

    double Point::getZ() const
    {
        return z;
    }

    double Point::distance(const Point& p) const
    {
        return (x - p.getX()) * (x - p.getX()) + (y - p.getY()) * (y - p.getY()) + (z - p.getZ()) * (z - p.getZ());
    }

    vector Point::vectTo(const Point& p) const
    {
        return vector(p.getX() - x, p.getY() - y, p.getZ() - z);
    }

    bool Point::operator!=(const Point& p) const
    {
    	return (std::fabs(x - p.getX()) > 0.0001)||(std::fabs(y - p.getY()) > 0.0001)||(std::fabs(z - p.getZ()) > 0.0001);
    }
}
