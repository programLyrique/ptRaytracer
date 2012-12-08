#include "ptScenes.h"

	Four_Spheres::Four_Spheres() :
		camera(rt::Point(0, 0, 0), rt::Point(0, 500, 0), rt::vector(0, 0, 1)),
		light(20., 0., 0., rt::color::WHITE, this),
		s1(rt::Sphere(rt::Point(3, 20, 0), 3, rt::Texture(rt::color::WHITE, rt::color(255, 255, 0), 100))),
		s2(rt::Sphere(rt::Point(-3, 20, 3), 3, rt::Texture(rt::color::WHITE, rt::color(255, 0, 255), 100))),
		s3(rt::Sphere(rt::Point(-3, 20, -3), 3, rt::Texture(rt::color::WHITE, rt::color(0, 255, 255), 100))),
		s4(rt::Sphere(rt::Point(3, 20, 6), 3, rt::Texture(rt::color::WHITE, rt::color::RED, 100)))
	{

		setCamera(&camera);
		addLight(&light);

		addSolid(&s1);
		addSolid(&s2);
		addSolid(&s3);
		addSolid(&s4);
	}

