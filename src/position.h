#ifndef POSITION_H
#define POSITION_H

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
            double distance(const Position& p);
    };

}

#endif //POSITION_H
