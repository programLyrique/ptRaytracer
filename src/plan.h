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
#include "mesh.h"
#include "position.h"
#include "vector.hpp"

namespace rt
{
	class Plan :	public Mesh {

		protected:


		private:
			Position point;
			vector normal;
		public:
			/** Constructor */
			Plan() {}
			~Plan() {}
			Plan(Texture t, const Position& p, vector n) : Mesh(t), point(p), normal(n.unit()) {}

			vector getNormal(const Position& p, const vector& vect) const;

			bool intersect(const Position& pos, const vector& vect);

			Position autreCote(const Position& point, const vector& vect, const Position& act) const;

			Position getIntersection(const Position& pos, const vector& vect);

	};
}

#endif //PLAN_H
