#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
    public:
        /** Default constructor */
        Camera();
        /** Access eye
         * \return The current value of eye
         */
        Position getEye() { return eye; }
        /** set eye
         * \param val New value to set
         */
        void setEye(Position val) { eye = val; }
        /** Access center
         * \return The current value of center
         */
        Position getCenter() { return center; }
        /** set center
         * \param val New value to set
         */
        void setCenter(Position val) { center = val; }
        /** Access up
         * \return The current value of up
         */
        vector getUp() { return up; }
        /** set up
         * \param val New value to set
         */
        void setUp(vector val) { up = val; }
    protected:
    private:
        Position eye; //!< Member variable "eye"
        Position center; //!< Member variable "center"
        vector up; //!< Member variable "up"
};

#endif // CAMERA_H
