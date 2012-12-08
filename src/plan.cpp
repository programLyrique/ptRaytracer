#include "plan.h"

namespace rt
{
	bool Plan::intersect(const Point& pos, const vector& vect) const
	{
		if((vect | normal) == 0)
			return false;
		double d = - (point.getX() * normal.x + point.getY() * normal.y + point.getZ() * normal.z);
		double t = - (normal.x * pos.getX() + normal.y * pos.getY() + normal.z * pos.getZ() + d) / (normal.x * vect.x + normal.y * vect.y + normal.z * vect.z);
		return t > 0;
	}

	Point Plan::getIntersection(const Point& pos, const vector& vect) const
	{
		double d = - (point.getX() * normal.x + point.getY() * normal.y + point.getZ() * normal.z);
		double t = - (normal.x * pos.getX() + normal.y * pos.getY() + normal.z * pos.getZ() + d) / (normal.x * vect.x + normal.y * vect.y + normal.z * vect.z);
		return Point(pos.getX() + t * vect.x, pos.getY() + t * vect.y, pos.getZ() + t * vect.z);
	}

	vector Plan::getNormal(const Point& p, const vector& vect) const
	{
        if((vect | normal) > 0)
			return normal;
		return -1 * normal;
	}

	Point Plan::autreCote(const Point& point, const vector& vect, const Point& act) const
	{
		return act;
	}

}
