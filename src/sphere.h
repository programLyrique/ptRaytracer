#ifndef SPHERE_H
#define SPHERE_H

namespace rt
{
    class Sphere:   public Mesh
    {
        protected:
            /// Center of the sphere
            int centre;
            
            /// Size of the sphere
            int rayon;
        private:
        public:
            /// default constructor
            Sphere();
            
            /// default destructor
            ~Sphere();
            
            /**
            * Constructor
            * @arg center
            * @arg rayon
            */
            Sphere(int _centre, int _rayon);
    };
}

#endif //SPHERE_H
