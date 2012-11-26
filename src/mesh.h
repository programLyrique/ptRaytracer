#ifndef MESH_H
#define MESH_H

namespace rt
{

class Mesh
{
    protected:
        /** Coefficient de reflexion */
        double reflexion;

        /** angle de réfraction*/
        double refraction;
    private:
    public:
        /** Default constructor */
        Mesh();
        /** Default destructor */
        virtual ~Mesh();

        /** Wether the camera intersects the mesh.
        *    @param camera the camera in the scene
        */
        virtual bool intersect(const Camera& camera) = 0;

        /** Wether the line defined by a vector and a point intersects the mesh.
        *    @param pos the point
        *    @param vect the vector
        */
        virtual bool intersect(const Position& pos, const vector& vect) = 0;

};

}

#endif // MESH_H
