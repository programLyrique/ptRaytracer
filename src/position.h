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
            int x;
            int y;
            int z;
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
    }

}

#endif //POSITION_H
