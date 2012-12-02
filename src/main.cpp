#include <iostream>
#include <unistd.h>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"

#define NB_SPHERES 50

int main(void)
{
    rt::screen s(1376,768);

    // here the code to draw the pixels...
    rt::Scene scene;
    scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 500, 0), rt::vector(0, 0, 1)));
    scene.addLight(new rt::PointLight(20., 25., 0., rt::color::WHITE, &scene));
    for(int k = 0 ; k < NB_SPHERES ; k++)
    {
        scene.addMesh(new rt::Sphere(rt::Position(10 + 2 * k, 25+3.5* k, 2.5 * k), 1, rt::Texture(rt::color::RED, rt::color::BLUE, 100)));
    }

    scene.render(s);


    while(s.update()) {

    }

    return 0;
}
