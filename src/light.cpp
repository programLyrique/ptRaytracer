#include "light.h"

namespace rt
{
    Light::Light()
    {

    }

    Light::~Light()
    {

    }

    Light::Light(color c, Scene* parent): couleur(c)
    {
        scene = parent;

    }

}
