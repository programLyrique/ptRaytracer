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

            /** Default constructor :
             * positionned et (0,0,0)
             */
            Position();

            /**
            * Constructor
            * @arg x
            * @arg y
            * @arg z
            */
            Position(double _x, double _y, double _z);

            /**
             * @return the abscissa of the point
             */
            double get_x() const;
            /**
             * @return the ordinate of the point
             */
            double get_y() const;
            /**
             * @return the height of the point
             */
            double get_z()const;

            /**
             * @arg x the abscissa of the point
             */
            void set_x(double x);
            /**
             * @arg y the ordinate of the point
             */
            void set_y(double y);
            /**
             * @arg z the height of the point
             */
            void set_z(double z);
    }

}

#endif //POSITION_H
