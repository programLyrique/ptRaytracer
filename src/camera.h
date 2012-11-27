#ifndef CAMERA_H
#define CAMERA_H

#include "position.h"
#include "vector.hpp"
#include "scene.h"

namespace rt
{
    /**
    * @todo Deciding the size of the screen - the portion of the world seen by
    * the camera
    */
    class Camera
    {
    public:
        /**  Set up the camera
         * @param eye the position of the camera
         * @param centre the point it looks to
         * @param up a vector directing the vertical direction
         */
        Camera(Position eye, Position centre, vector up, Scene& par);
        /** Access eye
         * \return The current value of eye
         */
        Position getEye() { return eye; };
        /** set eye
         * \param val New value to set
         */
        void setEye(Position val) { eye = val; };
        /** Access center
         * \return The current value of center
         */
        Position getCenter() { return center; };
        /** set center
         * \param val New value to set
         */
        void setCenter(Position val) { center = val; };
        /** Access up
         * \return The current value of up
         */
        vector getUp() { return up; };
        /** set up
         * \param val New value to set
         */
        void setUp(vector val) { up = val; };
        /** generate the scene from the point of view of the camera */
        void generate(int height, int width);

    protected:
    private:
        Position eye; //!< Member variable "eye"
        Position center; //!< Member variable "center"
        vector up; //!< Member variable "up"
        Scene& parent;
    };

}
#endif // CAMERA_H
