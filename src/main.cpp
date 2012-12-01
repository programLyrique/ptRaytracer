#include <iostream>
#include <unistd.h>
#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "light.h"
#include "pointlight.h"

int main(void)
{
	rt::screen s(640,480);

	// here the code to draw the pixels...
	rt::Scene scene;
	scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 100, 0), rt::vector(0, 0, 1)));
	scene.addMesh(new rt::Sphere(rt::Position(0, 15, 0), 10, rt::Texture(rt::color::BLUE, 1, 1., 1., 1., 1., 1., 1., 1., 1., 1.)));
	scene.addLight(new rt::PointLight(11., 15., 0., 5., 5., &scene));
	scene.render(s);


	while(s.update()) {

	}

	return 0;
}
