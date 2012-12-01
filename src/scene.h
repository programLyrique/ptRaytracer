#ifndef SCENE_H
#define SCENE_H

class Camera;
class Light;

#include "mesh.h"
#include "light.h"
#include "camera.h"
#include "screen.hpp"
#include "sphere.h"
#include <vector>
#include <cstdio>


namespace rt
{
    /**
     * A scene in which you can place meshes, lights, and cameras, and then, render it on a screen.
     * @todo Add anti-aliasing filter at the end of the rendering.
     */
    class Scene
    {
        protected:
        private:
            std::vector<Mesh*> objets;
            std::vector<Light*> lampes;
            Camera* cam;
        public:
            /** default constructor */
            Scene();

            /** default destructor */
            virtual ~Scene(){};

            /**
            * Add a mesh in the scene.
            */
            void addMesh(Mesh* mesh);//const ?

            /**
            * Add a light in the scene.
            */
            void addLight(Light* light);

            /**
            * Set the camera in the scene.
            * There is always only one camera !
            */
            void setCamera(Camera* camera);

            /**
             * Renders the scene on the screen.
             */
            void render(screen& s);
            
            std::vector<Mesh*>::const_iterator getDebObjets() { return objets.begin(); }
            std::vector<Mesh*>::const_iterator getFinObjets() { return objets.end(); }

    };
}

#endif //SCENE_H
