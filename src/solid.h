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
#ifndef MESH_H
#define MESH_H

#include "point.h"
#include "vector.hpp"
#include "texture.h"

namespace rt
{

class Solid
{
    /**
     * One of the building block of a scene : solid.
     * Can be a sphere ( @see Sphere ), or a cube...
     */
    protected:
        /** Coefficient de reflexion */
        double reflexion;

        /** angle de réfraction*/
        double refraction;

        /** Texture of the solid*/
        Texture t;
    private:
    public:
        /** Default constructor : puts uniform black as a texture. */
        Solid();

        /** @param texture the texture for the solid*/
        Solid(Texture texture);

        virtual ~Solid() {}

        /** Wether the line defined by a vector and a point intersects the solid.
        *    @param pos the point
        *    @param vect the vector
        */
        virtual bool intersect(const Point& pos, const vector& vect) = 0;


        /** get intersection between the object and a line if it exists
        * @param point the beginning of the ray
        * @param vect a directing vector of the ray
        * \return the intersection if it exists
        */
        virtual Point getIntersection(const Point& point, const vector& vect) = 0;

        /** Retourne un vecteur normal a la surface
        * @param point of the object
        * \return vector
        */
        virtual vector getNormal(const Point& p, const vector& v) const = 0;

        /** Accessor
        * \return texture of the solid
        */
        Texture getTexture() const { return t; } ;


};

}

#endif // MESH_H
