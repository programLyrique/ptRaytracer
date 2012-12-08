/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PLAN_H
#define PLAN_H

#include "texture.h"
#include "solid.h"
#include "point.h"
#include "vector.hpp"

namespace rt
{
	class Plan : public Solid {

		protected:


		private:
			Point point;
			vector normal;
		public:

			Plan() {}
			virtual ~Plan() {}
			/** Constructor
			* @param t texture
			* @param p point of the plane
			* @param n normal vector to the plane
			*/
			Plan(Texture t, const Point& p, vector n) : Solid(t), point(p), normal(n.unit()) {}

			vector getNormal(const Point& p, const vector& vect) const;

            /**
             * Calculations on the normal vector of the plane, and one of its point, to decide wether there is an
             * intersection.
             */
			bool intersect(const Point& pos, const vector& vect) const;

			Point autreCote(const Point& point, const vector& vect, const Point& act) const;


			Point getIntersection(const Point& pos, const vector& vect) const;

	};
}

#endif //PLAN_H
