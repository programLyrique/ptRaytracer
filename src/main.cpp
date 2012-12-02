#include <iostream>
#include <unistd.h>
#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"

int main(void)
{
	rt::screen s(640,480);

	// here the code to draw the pixels...
	rt::Scene scene;
	scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 5, 0), rt::vector(0, 0, 1)));
	scene.addMesh(new rt::Sphere(rt::Position(0, 15, 0), 14, rt::Texture(rt::color::BLUE)));
	scene.addMesh(new rt::Sphere(rt::Position(-50, 20, -3), 20, rt::Texture(rt::color::RED)));
	scene.render(s);

	while(s.update()) {

	}

	return 0;
}
