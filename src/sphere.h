#ifndef SPHERE_H
#define SPHERE_H

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

    };
}

#endif //SPHERE_H
