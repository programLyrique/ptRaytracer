#include <iostream>
#include <unistd.h>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"

#include <cmath>
#include <sstream>

#define NB_SPHERES 20

int main(int argc, char** argv)
{
    rt::screen s(640,480);

	// here the code to draw the pixels...
    rt::Scene scene;
    scene.setCamera(new rt::Camera(rt::Point(0, 0, 0), rt::Point(0, 500, 0), rt::vector(0, 0, 1)));
    scene.addLight(new rt::PointLight(0., 0., 0., rt::color::WHITE, &scene));
    /*scene.addLight(new rt::PointLight(-20, -25, 0, rt::color::WHITE, &scene));
    for(int k = 0 ; k < NB_SPHERES ; k++)
    {
        scene.addSolid(new rt::Sphere(rt::Point(0 * cos(k), 20 + 35* cos(k), 25 * cos(k) ), 3, rt::Texture(rt::color::RED, rt::color::BLUE, 1, 0, 1)));
    }
    scene.addSolid(new rt::Plan(rt::Texture(rt::color::WHITE, rt::color::WHITE, 1, 0, 1), rt::Point(0, 0, 10), rt::vector(0, 0, -1)));*/
	scene.addSolid(new rt::Sphere(rt::Point(3, 20, 0), 3, rt::Texture(rt::color::WHITE, rt::color(255, 255, 0), 100)));
	scene.addSolid(new rt::Sphere(rt::Point(-3, 20, 3), 3, rt::Texture(rt::color::WHITE, rt::color(255, 0, 255), 100)));
	scene.addSolid(new rt::Sphere(rt::Point(-3, 20, -3), 3, rt::Texture(rt::color::WHITE, rt::color(0, 255, 255), 100)));
	scene.addSolid(new rt::Sphere(rt::Point(0, 15, 0), 3, rt::Texture(rt::color::WHITE, rt::color::WHITE, 1)));
	scene.addSolid(new rt::Sphere(rt::Point(3, 20, 6), 3, rt::Texture(rt::color::WHITE, rt::color::RED, 100)));






    std::cout << "Nombre de param : " << argc << std::endl;

    //On peut passer le nombre de coeurs voulus en paramètre
    if(argc <= 1)
        scene.render(s);
    else
    {
        std::istringstream iss(argv[1]);
        int nbThreads;
        iss >> nbThreads;
        scene.render(s);
    }

    while(s.update()) {

    }

    return 0;
}
