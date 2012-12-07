#ifndef SCENES_H
#define SCENES_H

#include "scene.h"
#include "sphere.h"
#include "pointlight.h"
#include "camera.h"
#include "point.h"


/**
 * A scene to benchmark the ray tracer with lots of solids in the scene.
 */
class Many_Spheres : public rt::Scene
{
public:
    Many_Spheres();
    virtual ~Many_Spheres(){};
private:

};


/**
 * A scene to show the reflexions in the scene.
 */
class Four_Spheres_Reflexions : public rt::Scene
{
public:
    Four_Spheres_Reflexions(){};
    virtual ~Four_Spheres_Reflexions(){};
private:
};

/**
 * A scene with transparence and reflexions.
 */
class Real_Transparence : public rt::Scene
{
public:
    Real_Transparence();
    virtual ~Real_Transparence(){};
private:
    rt::Camera camera;
    rt::PointLight light;
    rt::Sphere s1;
    rt::Sphere s2;
    rt::Sphere s3;
    rt::Sphere s4;
    rt::Sphere s5;

};

#endif
