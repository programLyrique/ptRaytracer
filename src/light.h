#ifndef LIGHT_H
#define LIGHT_H

namespace rt
{

class Light
{
    protected:
    private:
    public:
        /** Default constructor */
        Light();
        /** Default destructor */
        virtual ~Light();

        /*!
        * Return the illumination of a point in a scene
        * @arg the scene one study
        * @arg the position one want to know the illumination
        */
        virtual double illuminate(Scene& scene, Position& position) = 0;

};

}

#endif // LIGHT_H
