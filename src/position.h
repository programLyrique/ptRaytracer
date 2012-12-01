#ifndef POSITION_H
#define POSITION_H

#include "vector.hpp"

namespace rt
{
    /**
     * Position of a point in 3Ds.
     */
    class Position
    {
        protected:
        private:
            /*!
            *  Coordinates correponding of the position in space
            */
            double x;
            double y;
            double z;
        public:

            /** default constructor */
            Position(){};

            /** default destructor */
            ~Position(){};

            /**
            * Constructor
            * @arg x
            * @arg y
            * @arg z
            */
            Position(int _x, int _y, int _z);

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
            double distance(const Position& p) const;
            
            
            /** Create a vector for current point to given point
            * @param point
            * \return vector
            */
            vector vectTo(const Position& p) const;
    };

}

#endif //POSITION_H
