#ifndef LIGHT_H
#define LIGHT_H

class Scene;

#include "scene.h"
#include "position.h"
#include "mesh.h"
#include "sphere.h"
#include "color.hpp"

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
            color couleur;
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
            Light(color c, Scene* parent);

            /**
            * Return the illumination of a point in a scene
            * @param the position wanted
            */
            virtual double illuminateR(const Position& position, const Mesh* m, const vector vision) = 0;
            virtual double illuminateG(const Position& position, const Mesh* m, const vector vision) = 0;
            virtual double illuminateB(const Position& position, const Mesh* m, const vector vision) = 0;                        

    };
}

#endif // LIGHT_H
