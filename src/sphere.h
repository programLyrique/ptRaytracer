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
#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "position.h"
#include "mesh.h"
#include "texture.h"

namespace rt
{
    /**
     * A mesh that is a sphere.
     */
    class Sphere:   public Mesh
    {
        protected:
            /** Center of the sphere */
            Position centre;

            /// Size of the sphere
            double radius;
        private:
        public:
            /**
             * Builds a sphere of center (0,0,0) and radius 10.
             */
            Sphere() {};

            /// default destructor
            ~Sphere() {};

            /**
            * Constructor
            * @param center
            * @param radius
            */
            Sphere(Position centre, double radius, Texture text);

            /**
             * Whether the given ray intersects the sphere
             * @param point the beginning of the ray
             * @param vect a directing vector of the ray
             */
            bool intersect(const Position& point, const vector& vect);

            /** get intersection between the sphere and a line if it exists
            * @param point the beginning of the ray
            * @param vect a directing vector of the ray
            * \return the intersection if it exists
            */
            Position getIntersection(const Position& point, const vector& vect);
            
            /**	get the point on the other side of the object
            *	\return the point
            */
            Position autreCote(const Position& point, const vector& vect, const Position& act) const;
            
            /** Return the normal at p at the sphere
            * \return vector
            */
            vector getNormal(const Position& p, const vector& vect) const;

            /** Accessor
            * \return centre
            */
            Position getCentre() const { return centre; }

    };
}

#endif //SPHERE_H
