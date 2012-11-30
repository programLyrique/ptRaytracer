#include "light.h"

namespace rt
{
    Light::Light()
    {

    }

    Light::~Light()
    {

    }

    Light::Light(double p, Scene* parent)
    {
        scene = parent;
        power = p;
    }

}
