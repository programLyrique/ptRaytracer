#ifndef SCENE_H
#define SCENE_H

#include "mesh.h"
#include "light.h"
#include "camera.h"

#include "screen.hpp"

#include <vector>

namespace rt
{
    class Scene
    {
        protected:
        private:
            std::vector<Mesh> objets;
            std::vector<Light> lampes;
            Camera cam;
        public:
            /** default constructor */
            Scene();

            /** default destructor */
            ~Scene(){};

            /**
            * Add a mesh in the scene.
            */
            void addMesh(const Mesh* mesh);//const ?

            /**
            * Add a light in the scene.
            */
            void addLight(const Light* light);

            /**
            * Set the camera in the scene.
            * There is always only one camera !
            */
            void setCamera(const Camera* camera);

            /**
             * Renders the scene on the screen.
             */
            void render(const screen& s);

    };
}

#endif //SCENE_H
