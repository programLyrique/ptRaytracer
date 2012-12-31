#include "plan.h"

namespace rt
{
	bool Plan::intersect(const Point& pos, const vector& vect) const
	{
		if((vect | norma) == 0)
			return false;
		double d = - (point.getX() * norma.x + point.getY() * norma.y + point.getZ() * norma.z);
		double t = - (norma.x * pos.getX() + norma.y * pos.getY() + norma.z * pos.getZ() + d) / (norma.x * vect.x + norma.y * vect.y + norma.z * vect.z);
		return t > 0;
	}

	Point Plan::getIntersection(const Point& pos, const vector& vect) const
	{
		double d = - (point.getX() * norma.x + point.getY() * norma.y + point.getZ() * norma.z);
		double t = - (norma.x * pos.getX() + norma.y * pos.getY() + norma.z * pos.getZ() + d) / (norma.x * vect.x + norma.y * vect.y + norma.z * vect.z);
		return Point(pos.getX() + t * vect.x, pos.getY() + t * vect.y, pos.getZ() + t * vect.z);
	}

	vector Plan::normal(const Point& p, const vector& vect) const
	{
        if((vect | norma) > 0)
			return norma;
		return -1 * norma;
	}

	Point Plan::autreCote(const Point& point, const vector& vect, const Point& act) const
	{
		return act;
	}

}
