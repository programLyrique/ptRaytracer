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
#include "point.h"
#include "solid.h"
#include "texture.h"

namespace rt
{
    /**
     * A solid that is a sphere.
     */
    class Sphere:   public Solid
    {
        protected:
            /** Center of the sphere */
            Point centre;

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
            * @param center the center of the sphere
            * @param radius the radius of the sphere
            * @param text the texture of the sphere
            */
            Sphere(Point centre, double radius, Texture text);

            /**
             * Whether the given ray intersects the sphere
             * @param point the beginning of the ray
             * @param vect a directing vector of the ray
             */
            bool intersect(const Point& point, const vector& vect) const;

            /** get intersection between the sphere and a line if it exists
            * @param point the beginning of the ray
            * @param vect a directing vector of the ray
            * \return the intersection if it exists
            */
            Point getIntersection(const Point& point, const vector& vect) const;

            /**	get the point on the other side of the object
            *	\return the point
            */
            Point autreCote(const Point& point, const vector& vect, const Point& act) const;

            /** Return the normal passing through p at the sphere
            * \return vector
            */
            vector getNormal(const Point& p, const vector& vect) const;

            /** Accessor
            * \return centre
            */
            Point getCentre() const { return centre; }

    };
}

#endif //SPHERE_H
