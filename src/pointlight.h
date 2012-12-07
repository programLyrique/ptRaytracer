/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "point.h"
#include "light.h"
#include "scene.h"
#include "solid.h"
#include <vector>
#include <algorithm>
#include "color.hpp"

namespace rt
{
    /**
     * A simple light : only one point, and isotropic.
     */
    class PointLight : public Light, public Point
    {
        protected:
        private:
        public:
            /** default constructor */
            PointLight() {}

            /** default destructor */
            ~PointLight() {}

            /**
            * Constructor from a point
            * @param x x coordinates
            * @param y y coordinates
            * @param z z coordinates
            * @param color color of the light
            * @param parent	parent scene
            */
            PointLight(double x, double y, double z, color c, Scene* parent);

            color illuminate(const Point& p, const Solid* m, const vector vision) const;


    };

}

#endif //POINTLIGHT_H
