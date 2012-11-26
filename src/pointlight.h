#ifndef POINTLIGHT_H
#define POINTLIGHT_H

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
            * @arg position of the source
            */
            PointLight(Position& pos);

    }

}

#endif //POINTLIGHT_H
