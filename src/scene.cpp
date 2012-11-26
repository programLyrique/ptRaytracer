#include "scene.h"

namespace rt
{
    Scene::Scene()
    {
        objets = new vector<Mesh>();
        cams = new vector<Camera>();
        lampes = new vector<Light>();
    }

    Scene::getCams()
    {
        return &cams;
    }

    Scene::getLampes()
    {
        return &lampes;
    }

    Scene::getObjets()
    {
        return &objets;
    }

}
