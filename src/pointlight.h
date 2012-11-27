#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "position.h"

namespace rt
{
    class PointLight
    {
        protected:
            /** position of the source */
            Position pos;
        private:
        public:
            /** default constructor */
            PointLight();

            /** default destructor */
            ~PointLight();

            /**
            * Constructor from a position
            * @param position of the source
            */
            PointLight(Position& pos);

    };

}

#endif //POINTLIGHT_H
