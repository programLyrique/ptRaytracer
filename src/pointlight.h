#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "position.h"
#include "light.h"
#include "scene.h"
#include "mesh.h"
#include <vector>

namespace rt
{
    /**
     * A simple light : only one point, and isotropic.
     */
    class PointLight : public Light, public Position
    {
        protected:
        private:
        public:
            /** default constructor */
            PointLight() {}

            /** default destructor */
            ~PointLight() {}

            /**
            * Constructor from a position
            * @param x
            * @param y
            * @param z
            * @param power
            */
            PointLight(double x, double y, double z, double powerD, double powerS, Scene* parent);

            int illuminateR(const Position& p, const Sphere* m, const vector vision);
            int illuminateG(const Position& p, const Sphere* m, const vector vision);
            int illuminateB(const Position& p, const Sphere* m, const vector vision);

    };

}

#endif //POINTLIGHT_H
