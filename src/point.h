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
#ifndef POSITION_H
#define POSITION_H

#include "vector.hpp"
#include <cstdio>
#include <algorithm>
#include <cmath>

namespace rt
{
    /**
     * Point of a point in 3Ds.
     */
    class Point
    {
        protected:
        private:
            /**
            *  Coordinates correponding of the point in space
            */
            double x;
            double y;
            double z;
        public:

            /** default constructor */
            Point(){};

            /** default destructor */
            ~Point(){};

            /**
            * Constructor
            * @param x
            * @param y
            * @param z
            */
            Point(double _x, double _y, double _z);

            /** Accessors
            * \return x
            */
            double getX() const;
            /** Accessors
            * \return y
            */
            double getY() const;
            /** Accessors
            * \return z
            */
            double getZ() const;

            /** distances between 2 points
            * @arg other point
            */
            double distance(const Point& p) const;


            /** Create a vector for current point to given point
            * @param point
            * \return vector
            */
            vector vectTo(const Point& p) const;

            /**
            * Print the coordinates of the point
            */
            void print() const {
            	printf("%f %f %f\n", x, y, z);
            }

    		virtual bool operator!=(const Point& p) const;
    };

}

#endif //POSITION_H
