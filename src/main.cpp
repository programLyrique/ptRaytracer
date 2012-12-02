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
	scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 500, 0), rt::vector(0, 0, 1)));
	scene.addMesh(new rt::Sphere(rt::Position(0, 7, 0), 1, rt::Texture(rt::color::WHITE, rt::color::WHITE, 10)));
	scene.addLight(new rt::PointLight(10., 0., 0., 5., 5., &scene));
	scene.addMesh(new rt::Sphere(rt::Position(0, 15, 0), 5, rt::Texture(rt::color::RED, rt::color::WHITE, 10)));
	scene.render(s);


	while(s.update()) {

	}

	return 0;
}
