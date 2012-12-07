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


Many_Spheres::Many_Spheres(int nbSpheres) :
    camera(rt::Point(0, 0, 0), rt::Point(0, 500, 0), rt::vector(0, 0, 1)),
    light(-20, -25, 0, rt::color::WHITE, this),
    solids(nbSpheres),
    plan(rt::Texture(rt::color::WHITE, rt::color::WHITE, 1, 0, 1), rt::Point(0, 0, 10), rt::vector(0, 0, -1))
{
    addLight(&light);
    for(int k = 0 ; k < nbSpheres ; k++)
    {
        rt::Sphere* solid = new rt::Sphere(rt::Point(0 * cos(k), 20 + 35* cos(k), 25 * cos(k) ),
                                          3, rt::Texture(rt::color::RED, rt::color::BLUE, 1, 0, 1));
        solids[k] = solid;
        addSolid(solid);
    }
    addSolid(&plan);
}

Many_Spheres::~Many_Spheres()
{
    for(int k = 0; k < static_cast<int>(solids.size()); k++)
        delete solids[k];
}

Many_Spheres::Many_Spheres(const Many_Spheres& mS)
{
    camera = mS.camera;
    plan = mS.plan;
    for(int k = 0; k < static_cast<int>(solids.size()) ; k ++)
    {
        rt::Sphere* solid = new rt::Sphere;
        *solid = *(mS.solids[k]);

    }
}
