#ifndef LIGHT_H
#define LIGHT_H

class Scene;
#include "scene.h"
#include "position.h"
#include "mesh.h"
#include "sphere.h" 

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
            virtual int illuminateR(const Position& position, const Sphere* m, const vector vision) = 0;
            virtual int illuminateG(const Position& position, const Sphere* m, const vector vision) = 0;
            virtual int illuminateB(const Position& position, const Sphere* m, const vector vision) = 0;                        

    };
}

#endif // LIGHT_H
