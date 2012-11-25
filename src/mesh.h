#ifndef MESH_H
#define MESH_H

namespace rt
{

class Mesh
{
    protected:
    private:
    public:
        /** Default constructor */
        Mesh();
        /** Default destructor */
        virtual ~Mesh();

        /** Wether the camera intersects the mesh.
            @arg camera the camera in the scene
        */
        virtual bool intersect(Camera* camera) = 0;

};

}

#endif // MESH_H
