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
    scene.setCamera(new rt::Camera(rt::Point(0, 0, 0), rt::Point(0, 500, 0), rt::vector(0, 0, 1)));
    scene.addLight(new rt::PointLight(0., 0., 0., rt::color::WHITE, &scene));
    //scene.addLight(new rt::PointLight(-20, -25, 0, rt::color::WHITE, &scene));
	
	scene.addSolid(new rt::Sphere(rt::Point(0, 20, 5), 3, rt::Texture(rt::color::WHITE, rt::color(0, 255, 255), 100, 0, 1)));
	scene.addSolid(new rt::Sphere(rt::Point(0, 15, 0), 5, rt::Texture(rt::color::BLACK, rt::color::RED, 100, 0.5, 1.4)));
	





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
