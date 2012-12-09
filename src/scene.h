/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SCENE_H
#define SCENE_H

/** @mainpage
 * @version 0.5
 *
 * The ptRaytracer aims at enhancing your visual experience. It uses ray tracing technics to show realistic images.
 *
 * That version adds reflexion, transparence, multithreading, and anti-aliasing.
 */

class Camera;
class Light;

#include "solid.h"
#include "light.h"
#include "camera.h"
#include "screen.hpp"
#include "sphere.h"
#include "point.h"
#include "thread.h"

#include <vector>
#include <iostream>
#include <ctime>


namespace rt
{

/** A rectangle */
struct rectangle
{
    int x;
    int y;
    int sX;
    int sY;
};
/** A render queue that gives the coordinates of the next square to render.
 * default size of a square : 32 x 32.
 */
class RenderQueue
{
private:
    int nbW;
    int nbH;
    int reminderW;
    int reminderH;
    int w;
    int h;
    int tileLength;//size of a tile
public:
    /**
     * Init the render queue.
     * @param width width of the image
     * @param height height of the image
     * @param tile size of an elementary square. Default value : 32
     */
    RenderQueue(int width, int height, int tile=32);
    /** Gives the rectangle to render.
     * @warning Always verify wether all the tiles have been attributed with
     * noMoreTiles().
     */
    rectangle nextTile();
    /** Gives the length of a default tile.
     */
     int getTileLength() const;

     /** You have to call this method before each calling to nextTile().
      * @return true you can grab a new tile to render
      * @return false no more tiles
      */
      bool enoughTiles() const;

     friend std::ostream& operator<<(std::ostream& out, const RenderQueue& rdQ);
};

/**
 * A scene in which you can place meshes, lights, and cameras, and then, render it on a screen.
 */
class Scene
{
private:
    std::vector<Solid*> objets;
    std::vector<Light*> lights;
    Camera* cam;

    Mutex mutex;

    /**
     * Internal class to implement a rendering thread.
     * @see Thread
     */
    //friend class ThreadRender;
    class ThreadRender : public Thread
    {
    public:
        ThreadRender(Scene& _sc,RenderQueue& rdQueue,screen& _s);
        void run();
    private:
        Scene& sc;
        RenderQueue& renderQueue;
        screen& s;
    };

protected:
    /**
     * Renders a rectangle of the scene.
     * @param x x-coordinate of the left-upper vertex
     * @param y y-coordinate of the left-upper vertex
     * @param width width of the rectangle
     * @param height of the rectangle
     * @param oversampling if true, calculate 9 virtual pixels
     */
    void renderArea(int x, int y, int width, int height, screen& s, bool oversampling);
public:
    /** default constructor */
    Scene();

    /** default destructor */
    virtual ~Scene();

    /**
    * Add a mesh in the scene.
    */
    void addSolid(Solid* solid);

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
     * Detects the number of cores on the computer, and execute as many threads as there are cores
     * to render the scene.
     */
    void render(screen& s);

    /** The transparency coefficient after going throught the element between the 2 points
     * @param deb the first point
     * @param fin the second point
     */
    double existInterBetween(const Point& begin, const Point& end) const;

    /** Accessor
     * @return camera
     */

    Camera* getCamera() const
    {
        return cam;
    }

    /**
     * Number of objects in the scene
     */
    int getNbObjects() const
    {
        return objets.size();
    }

    /**
     * Number of lights in the scene.
     */
    int getNbLights() const
    {
        return lights.size();
    }

    /**
     * Renders the scene on the screen .
     * @param nbThreads number of threads to render the scene.
     * @todo Handling the case when nbThreads is not a power of two !
     * @todo Using a better cutting of the image : a circular list with threads that render
     * little square of the image.
     */
    void render(screen& s, int nbThreads);

    /** determine the illumination of the point on the solid
    * @param p the point
    * @param o the solid
    * @param v the vision direction
    * @param nbR the number of reflections
    * @param nbTrans the number of transmissions
    */
    color getIllumination(const Point& p, Solid* o, const vector& v, int nbR, int nbTrans) const;
};

}

#endif //SCENE_H

