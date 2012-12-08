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
#ifndef SCENES_H
#define SCENES_H

#include "scene.h"
#include "sphere.h"
#include "pointlight.h"
#include "camera.h"
#include "point.h"

/**
 * A basic scene with 4 sphere to show the Phong reflection model.
 */
class Four_Spheres : public rt::Scene
{
public:
    Four_Spheres();
    virtual ~Four_Spheres(){};
private:
    rt::Camera camera;
    rt::PointLight light1;
    rt::PointLight light2;
    rt::Sphere s1;
    rt::Sphere s2;
    rt::Sphere s3;
    rt::Sphere s4;
};

#endif
