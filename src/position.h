#ifndef POSITION_H
#define POSITION_H

namespace rt
{
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
            Position();

            /** default destructor */
            ~Position();

            /**
            * Constructor
            * @arg x
            * @arg y
            * @arg z
            */
            Position(int _x, int _y, int _z);

            /** Accessors */
            double getX() const;
            double getY() const ;
            double getZ() const;
    };

}

#endif //POSITION_H
