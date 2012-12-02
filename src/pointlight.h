#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "position.h"
#include "light.h"
#include "scene.h"
#include "mesh.h"
#include <vector>
#include <algorithm>
#include "color.hpp"

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
            * @param color
            * @param parent
            */
            PointLight(double x, double y, double z, color c, Scene* parent);

            double illuminateR(const Position& p, const Mesh* m, const vector vision);
            double illuminateG(const Position& p, const Mesh* m, const vector vision);
            double illuminateB(const Position& p, const Mesh* m, const vector vision);

    };

}

#endif //POINTLIGHT_H
