#ifndef LIGHT_H
#define LIGHT_H

class Scene;
#include "scene.h"
#include "position.h"
#include "Mesh.h"

namespace rt
{
    /**
     * The building blocks of a light.
     */
    class Light
    {
        protected:
            /** Parent scene */
            Scene* scene;
            double powerD;
            double powerS;
        private:
        public:
            /** Default constructor */
            Light();
            /** Default destructor */
            virtual ~Light();

            /** Constructor
            * @aram power
            * @param Parent scene
            */
            Light(double pD, double pS, Scene* parent);

            /**
            * Return the illumination of a point in a scene
            * @param the position wanted
            */
            virtual double illuminate(const Position& position, const Sphere* m) = 0;

    };
}

#endif // LIGHT_H
