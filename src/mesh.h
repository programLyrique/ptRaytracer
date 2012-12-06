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

#include "position.h"
#include "vector.hpp"
#include "texture.h"

namespace rt
{

class Mesh
{
    /**
     * One of the building block of a scene : mesh.
     * Can be a sphere ( @see Sphere ), or a cube...
     */
    protected:
        /** Coefficient de reflexion */
        double reflexion;

        /** angle de réfraction*/
        double refraction;

        /** Texture of the mesh*/
        Texture t;
    private:
    public:
        /** Default constructor : puts uniform balck as a texture. */
        Mesh();

        /** @param texture the texture for the mesh*/
        Mesh(Texture texture);

        /** Wether the line defined by a vector and a point intersects the mesh.
        *    @param pos the point
        *    @param vect the vector
        */
        virtual bool intersect(const Position& pos, const vector& vect) = 0;


        /** get intersection between the object and a line if it exists
        * @param point the beginning of the ray
        * @param vect a directing vector of the ray
        * \return the intersection if it exists
        */
        virtual Position getIntersection(const Position& point, const vector& vect) = 0;

        /** Return the point on the other side of the mesh
        * \return point
     	*/
        virtual Position autreCote(const Position& point, const vector& vect, const Position& act) const = 0;


        /** Retourne un vecteur normal a la surface
        * @param point of the object
        * \return vector
        */
        virtual vector getNormal(const Position& p, const vector& v) const = 0;

        /** Accessor
        * \return texture of the mesh
        */
        Texture getTexture() const { return t; } ;


};

}

#endif // MESH_H
