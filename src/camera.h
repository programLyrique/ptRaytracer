/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "position.h"
#include "vector.hpp"
#include "scene.h"

namespace rt
{
    /**
     * A camera.
     * Quite a simple perspective one : you give an vertical direction, a position where is the camera
     * and a position where the camera looks at.
     * @todo Deciding the size of the screen - the portion of the world seen by
     * the camera
     */
    class Camera
    {
		public:
		    Camera(){};///A default constructor @todo To remove it !
		    /**  Set up the camera
		     * @param eye the position of the camera
		     * @param centre the point it looks to
		     * @param up a vector directing the vertical direction
		     */
		    Camera(Position eye, Position centre, vector _up/*, Scene* par*/);
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
		    Position getCentre() { return centre; };
		    /** set center
		     * \param val New value to set
		     */
		    void setCenter(Position val) { centre = val; };
		    /** Access up
		     * \return The current value of up
		     */
		    vector getUp() { return up; };
		    /** set up
		     * \param val New value to set
		     */
		    void setUp(vector val) { up = val; };

		protected:
		private:
		    Position eye; //!< Member variable "eye"
		    Position centre; //!< Member variable "centre"
		    vector up; //!< Member variable "up"
		    Scene* parent;
		};

}
#endif // CAMERA_H
