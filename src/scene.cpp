#include "scene.h"

namespace rt
{
    Scene::Scene()
    {
        objets = new std::vector<Mesh>();
        cams = new std::vector<Camera>();
        lampes = new std::vector<Light>();
    }



}
