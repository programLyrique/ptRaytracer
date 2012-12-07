#include "ptScenes.h"

Real_Transparence::Real_Transparence() :
    camera(rt::Point(0, 0, 0), rt::Point(0, 500, 0), rt::vector(0, 0, 1)),
    light(0., 0., 0., rt::color::WHITE, this),
    s1(rt::Point(3, 20, 0), 3, rt::Texture(rt::color::WHITE, rt::color(255, 255, 0), 100, 0, 1)),
    s2(rt::Point(-3, 20, 3), 3, rt::Texture(rt::color::WHITE, rt::color(255, 0, 255), 100, 0, 1)),
    s3(rt::Point(-3, 20, -3), 3, rt::Texture(rt::color::WHITE, rt::color(0, 255, 255), 100, 0, 1)),
    s4(rt::Point(0, 15, 0), 3, rt::Texture(rt::color::WHITE, rt::color::WHITE, 1, 0.9, 1.4)),
    s5(rt::Point(3, 20, 6), 3, rt::Texture(rt::color::WHITE, rt::color::RED, 100, 0, 1))

{
    setCamera(&camera);

    addLight(&light);

	addSolid(&s1);
	addSolid(&s2);
	addSolid(&s3);
	addSolid(&s4);
	addSolid(&s5);

}

Four_Spheres_Reflexions::Four_Spheres_Reflexions() :
    camera(rt::Point(0, 0, 0), rt::Point(0, 500, 0), rt::vector(0, 0, 1)),
    light(0., 0., 0., rt::color::WHITE, this),
    s1(rt::Point(3, 20, 0), 3, rt::Texture(rt::color(255, 255, 0), rt::color::WHITE, 1000, 0, 1)),
    s2(rt::Point(-3, 20, 3), 3, rt::Texture(rt::color(255, 0, 255), rt::color::WHITE, 1000, 0, 1)),
    s3(rt::Point(-3, 20, -3), 3, rt::Texture(rt::color(0, 255, 255), rt::color::WHITE, 1000, 0, 1)),
    s4(rt::Point(3, 20, 6), 3, rt::Texture(rt::color::RED, rt::color::WHITE, 1000, 0, 1))
{

    setCamera(&camera);
    addLight(&light);

    addSolid(&s1);
    addSolid(&s2);
    addSolid(&s3);
    addSolid(&s4);
}


Many_Spheres::Many_Spheres()
{
       /*scene.addLight(new rt::PointLight(-20, -25, 0, rt::color::WHITE, &scene));
    for(int k = 0 ; k < NB_SPHERES ; k++)
    {
        scene.addSolid(new rt::Sphere(rt::Point(0 * cos(k), 20 + 35* cos(k), 25 * cos(k) ), 3, rt::Texture(rt::color::RED, rt::color::BLUE, 1, 0, 1)));
    }
    scene.addSolid(new rt::Plan(rt::Texture(rt::color::WHITE, rt::color::WHITE, 1, 0, 1), rt::Point(0, 0, 10), rt::vector(0, 0, -1)));*/
}
