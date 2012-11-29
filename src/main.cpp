#include <iostream>
#include <unistd.h>
#include "screen.hpp"
#include "scene.h"

int main(void)
{
	rt::screen s(640,480);

	// here the code to draw the pixels...
	rt::Scene scene;
	scene.setCamera(new rt::Camera(rt::Position(0, 0, 0), rt::Position(0, 5, 0), rt::vector(0, 0, 1)));
	scene.addMesh(new rt::Sphere(rt::Position(0, 15, 0), 11));
	scene.render(s);

	while(s.update()) {

	}

	return 0;
}
