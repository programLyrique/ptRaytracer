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
    scene.addLight(new rt::PointLight(20., 0., 0., rt::color::WHITE, &scene));
	scene.addSolid(new rt::Sphere(rt::Point(3, 20, 0), 3, rt::Texture(rt::color::WHITE, rt::color(255, 255, 0), 100)));
	scene.addSolid(new rt::Sphere(rt::Point(-3, 20, 3), 3, rt::Texture(rt::color::WHITE, rt::color(255, 0, 255), 100)));
	scene.addSolid(new rt::Sphere(rt::Point(-3, 20, -3), 3, rt::Texture(rt::color::WHITE, rt::color(0, 255, 255), 100)));
	scene.addSolid(new rt::Sphere(rt::Point(3, 20, 6), 3, rt::Texture(rt::color::WHITE, rt::color::RED, 100)));

    scene.render(s);

    while(s.update()) {

    }

    return 0;
}
