#ifndef MESH_H
#define MESH_H

#include "position.h"
#include "vector.hpp"
#include "texture.h"

namespace rt
{

class Mesh
{
    protected:
        /** Coefficient de reflexion */
        double reflexion;

        /** angle de réfraction*/
        double refraction;
    private:
    public:
        /** Default constructor */
        Mesh();

        /** Wether the line defined by a vector and a point intersects the mesh.
        *    @param pos the point
        *    @param vect the vector
        */
        virtual bool intersect(const Position& pos, const vector& vect) = 0;
        virtual Texture getTexture() = 0;

};

}

#endif // MESH_H
