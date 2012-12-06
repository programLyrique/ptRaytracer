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
            * @param power
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
