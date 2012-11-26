#include "scene.h"

namespace rt
{
    Scene::Scene()
    {
        objets = new std::vector<Mesh>();
        cams = new std::vector<Camera>();
        lampes = new std::vector<Light>();
    }

    std::vector<Camera> Scene::getCams()
    {
        return &cams;
    }

    std::vector<Light> Scene::getLampes()
    {
        return &lampes;
    }

    std::vector<Mesh> Scene::getObjets()
    {
        return &objets;
    }

}
