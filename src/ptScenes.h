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

#include <vector>

#include "scene.h"
#include "sphere.h"
#include "pointlight.h"
#include "camera.h"
#include "point.h"
#include "plan.h"
#include "bumpmap.h"

/**
 * A scene to benchmark the ray tracer with lots of solids in the scene.
 */
class Many_Spheres : public rt::Scene
{
public:
    /**   Creates a scene with a huge pile of spheres
     * @param nbSpheres number of spheres. Not more 1000 if you want a render time of less than 15 minutes.
     * 100 takes 39 s to render on an octocore (core i7, 2,6 GHz).
     */
    Many_Spheres(int nbSpheres);
    virtual ~Many_Spheres();
    /** A copy constructor.
     * But you really don't need to coyp that class !
     */
    Many_Spheres(const Many_Spheres& mS);

    /**
     * Overloading =
     * But you really don't need to use = with that class !
     */
    Many_Spheres& operator = (const Many_Spheres& mS);
private:
    rt::Camera camera;
    rt::PointLight light;
    std::vector<rt::Sphere* > spheres;
    rt::Plan plan;
};


/**
 * A scene to show the reflexions in the scene.
 */
class Four_Spheres_Reflexions : public rt::Scene
{
public:
    Four_Spheres_Reflexions();
    virtual ~Four_Spheres_Reflexions(){};
private:
    rt::Camera camera;
    rt::PointLight light;
    rt::Sphere s1;
    rt::Sphere s2;
    rt::Sphere s3;
    rt::Sphere s4;
};

/**
 * A scene with transparence and reflexions.
 */
class Real_Transparence : public rt::Scene
{
public:
    Real_Transparence();
    virtual ~Real_Transparence(){delete bmap;};
private:
    rt::ProceduralBumpmap* bmap;
    rt::Camera camera;
    rt::PointLight light;
    rt::Sphere s1;
    rt::Sphere s2;
    rt::Sphere s3;
    rt::Sphere s4;
    rt::Sphere s5;

};

#endif
