#include <iostream>
#include <unistd.h>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"

#include <cmath>

#define NB_SPHERES 100

int main(void)
{
    rt::screen s(1376,768);

    // here the code to draw the pixels...
    rt::Scene scene;
    scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 500, 0), rt::vector(0, 0, 1)));
    scene.addLight(new rt::PointLight(20., 25., 0., rt::color::WHITE, &scene));
    scene.addLight(new rt::PointLight(-20, -25, 0, rt::color::WHITE, &scene));
    for(int k = 0 ; k < NB_SPHERES ; k++)
    {
        scene.addMesh(new rt::Sphere(rt::Position(0 * cos(k), 20 + 35* cos(k), 25 * cos(k) ), 3, rt::Texture(rt::color::RED, rt::color::WHITE, 10, 0.9, 5)));
    }
    scene.addMesh(new rt::Sphere(rt::Position(20, 20, 0), 3, rt::Texture(rt::color::BLACK, rt::color::WHITE, 100, 0, 5)));
    scene.addMesh(new rt::Sphere(rt::Position(0, 35, 0), 5, rt::Texture(rt::color::GREEN, rt::color::BLACK, 100, 0, 1)));
    

    scene.render(s);


    while(s.update()) {

    }

    return 0;
}
