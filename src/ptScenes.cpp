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
    s1(rt::Point(3, 20, 0), 3, rt::Texture(rt::color::WHITE, rt::color(255, 255, 0), 1000, 0, 1)),
    s2(rt::Point(-3, 20, 3), 3, rt::Texture(rt::color::WHITE, rt::color(255, 0, 255), 1000, 0, 1)),
    s3(rt::Point(-3, 20, -3), 3, rt::Texture(rt::color::WHITE, rt::color(0, 255, 255), 1000, 0, 1)),
    s4(rt::Point(3, 20, 6), 3, rt::Texture(rt::color::WHITE, rt::color::RED, 1000, 0, 1))
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
    spheres(nbSpheres),
    plan(rt::Texture(rt::color::WHITE, rt::color::WHITE, 1, 0, 1), rt::Point(0, 0, 10), rt::vector(0, 0, -1))
{
	setCamera(&camera);
    addLight(&light);
    for(int k = 0 ; k < nbSpheres ; k++)
    {
        rt::Sphere* sphere = new rt::Sphere(rt::Point(0 * cos(k), 20 + 35* cos(k), 25 * cos(k) ),
                                          3, rt::Texture(rt::color::BLUE, rt::color::RED, 1, 0, 1));
        spheres[k] = sphere;
        addSolid(sphere);
    }
    addSolid(&plan);
}

Many_Spheres::~Many_Spheres()
{
    for(int k = 0; k < static_cast<int>(spheres.size()); k++)
        delete spheres[k];
}

Many_Spheres::Many_Spheres(const Many_Spheres& mS)
{
    camera = mS.camera;
    plan = mS.plan;
    spheres.resize(mS.spheres.size());
    for(int k = 0; k < static_cast<int>(spheres.size()) ; k ++)
    {
        rt::Sphere* sphere = new rt::Sphere;
        *sphere = rt::Sphere(*(mS.spheres[k]));
        spheres[k] = sphere;

    }
}


 Many_Spheres& Many_Spheres::operator = (const Many_Spheres& mS)
 {
    if(this != &mS)
    {
        camera = mS.camera;
        plan = mS.plan;
        spheres.resize(mS.spheres.size());
        for(int k = 0; k < static_cast<int>(spheres.size()) ; k ++)
        {
            rt::Sphere* sphere = new rt::Sphere;
            *sphere = rt::Sphere(*(mS.spheres[k]));
            spheres[k] = sphere;

        }
    }
    return *this;
 }

