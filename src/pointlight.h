#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "position.h"
#include "light.h"
#include "scene.h"
#include "mesh.h"
#include <vector>
#include <algorithm>

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

            double illuminateR(const Position& p, const Mesh* m, const vector vision);
            double illuminateG(const Position& p, const Mesh* m, const vector vision);
            double illuminateB(const Position& p, const Mesh* m, const vector vision);

    };

}

#endif //POINTLIGHT_H
