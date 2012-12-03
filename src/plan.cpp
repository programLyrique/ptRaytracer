#include "plan.h"

namespace rt
{
	bool Plan::intersect(const Position& pos, const vector& vect)
	{
		if((vect | normal) == 0)
			return false;
		return ((pos.vectTo(point) | vect) > 0);
	}
	
	Position Plan::getIntersection(const Position& pos, const vector& vect)
	{
		double d = - (point.getX() * normal.x + point.getY() * normal.y + point.getZ() * normal.z);
		double t = - (normal.x * pos.getX() + normal.y * pos.getY() + normal.z * pos.getZ() + d) / (normal.x * vect.x + normal.y * vect.y + normal.z * vect.z);
		return Position(pos.getX() + t * vect.x, pos.getY() + t * vect.y, pos.getZ() + t * vect.z);
	}
	
	Position Plan::autreCote(const Position& point, const vector& vect, const Position& act) const
	{
		return act;
	}

}
