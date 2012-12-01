#ifndef SCENE_H
#define SCENE_H

class Camera;
class Light;

#include "mesh.h"
#include "light.h"
#include "camera.h"
#include "screen.hpp"
#include "sphere.h"
#include "thread.h"

#include <vector>


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

            /**
             * Renders a rectangle of the scene.
             * @param x x-coordinate of the left-upper vertex
             * @param y y-coordinate of the left-upper vertex
             * @param width width of the rectangle
             * @param height of the rectangle
             */
            void renderArea(unsigned x, unsigned y, unsigned width, unsigned height, screen& s);

            /**
             * Calculate the binary log of nb
             */
             //static unsigned b_log(unsigned nb);
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
            void addLight(const Light* light);

            /**
            * Set the camera in the scene.
            * There is always only one camera !
            */
            void setCamera(Camera* camera);

            /**
             * Renders the scene on the screen.
             * Detects the number of cores on the computer, and execute as many threads as there are cores
             * to render the scene.
             */
            void render(screen& s);

            /**
             * Renders the scene on the screen .
             * @param nbThreads number of threads to render the scene.
             */
            void render(screen& s, unsigned nbThreads);
    };
}

#endif //SCENE_H
