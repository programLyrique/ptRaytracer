#include <iostream>
#include <unistd.h>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"
#include "plan.h"

#include <cmath>
#include <sstream>

#define NB_SPHERES 20

int main(int argc, char** argv)
{
    rt::screen s(640,480);

    // here the code to draw the pixels...
    rt::Scene scene;
    scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 500, 0), rt::vector(0, 0, 1)));
    scene.addLight(new rt::PointLight(20., 25., 0., rt::color::WHITE, &scene));
    scene.addLight(new rt::PointLight(-20, -25, 0, rt::color::WHITE, &scene));
    for(int k = 0 ; k < NB_SPHERES ; k++)
    {
        scene.addMesh(new rt::Sphere(rt::Position(0 * cos(k), 20 + 35* cos(k), 25 * cos(k) ), 3, rt::Texture(rt::color::RED, rt::color::BLUE, 1, 0, 1)));
    }
    scene.addMesh(new rt::Plan(rt::Texture(rt::color::WHITE, rt::color::WHITE, 1, 0, 1), rt::Position(0, 0, 10), rt::vector(0, 0, -1)));

    std::cout << "Nombre de param : " << argc << std::endl;

    //On peut passer le nombre de coeurs voulus en paramètre
    if(argc <= 1)
        scene.render(s);
    else
    {
        std::istringstream iss(argv[1]);
        int nbThreads;
        iss >> nbThreads;
        scene.render(s, nbThreads);
    }

    while(s.update()) {

    }

    return 0;
}
