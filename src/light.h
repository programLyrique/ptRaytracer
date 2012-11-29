#ifndef LIGHT_H
#define LIGHT_H

class Scene;
#include "scene.h"

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
        private:
        public:
            /** Default constructor */
            Light();
            /** Default destructor */
            virtual ~Light();

            /** Constructor
            * @param Parent scene
            */
            Light(Scene* _scene);

            /**
            * Return the illumination of a point in a scene
            * @param the position wanted
            */
            virtual double illuminate(const Position& position) = 0;

    };
}

#endif // LIGHT_H
