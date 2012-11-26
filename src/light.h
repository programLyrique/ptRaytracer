#ifndef LIGHT_H
#define LIGHT_H

namespace rt
{

class Light
{
    protected:
        /** Parent scene */
        Scene scene;
    private:
    public:
        /** Default constructor */
        Light();
        /** Default destructor */
        virtual ~Light();

        /**
        * Return the illumination of a point in a scene
        * @arg the position wanted
        */
        virtual double illuminate(const Position& position) = 0;

};

}

#endif // LIGHT_H
