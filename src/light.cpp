#include "light.h"

namespace rt
{
    Light::Light()
    {

    }

    Light::~Light()
    {

    }

    Light::Light(double pD, double pS, Scene* parent)
    {
        scene = parent;
        powerS = pS;
        powerD = pD;
    }

}
