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
        
        
        /** Retourne un vecteur normal a la surface 
        * @param point of the object
        * \return vector
        */
        virtual vector getNormal(const Position& p) const = 0;

        /** Accessor
        * \return texture of the mesh
        */
        Texture getTexture() const { return t; } ;


};

}

#endif // MESH_H
