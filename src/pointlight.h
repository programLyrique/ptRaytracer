#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "position.h"
#include "light.h"
#include "scene.h"

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
            PointLight(double x, double y, double z, double power, Scene* parent);

            double illuminate(const Position& p, const Mesh* m);

    };

}

#endif //POINTLIGHT_H
