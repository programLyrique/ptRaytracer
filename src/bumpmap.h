#ifndef BUMPMAP_H
#define BUMPMAP_H

#include "point.h"
#include "vector.hpp"

namespace rt
{

/**
 * A basic noise : simplex noise.
 *
 * Why not Perlin Noise ? Simplex noise is quicker in 3D, and has no artefacts due to axes.
 *
 * Useful to build a procedural bumpmap, or to create procedural textures.
 *
 * Thanks to Stefan Gustavson for his paper about the Simplex noise.
 *
 * Inspired (and transposed to 3D by me) by a code there : https://gist.github.com/2372043
 */
class SimplexNoise
{
    private:
        static const vector grad3[12];
        static const int p[256];
        static int perm[512];
        static int permMod12[512];
        static bool isInit;

        /* floor in cmath.h is fairly slow because of its support of the IEEE norm,
            which w dont' need here
        */
        static int inline fastfloor(double x)
        {
            int temp = static_cast<int>(x);
            return temp >=0 ? temp : temp-1;
        }
        SimplexNoise(){}; //No need to instantiate that class.
        /**
         * Initialize permutation tables.
         */
        static void init();
    public:
        /**
         * Simplex noise at the point p.
         * It is a gradient noise, interpolated in a simplex of the space (i.e. the simpliest shape
         * to fill the space, in 3D, a kind of tetrahedon !)
         */
        static double noise(const Point& p);
        static double noise(double x, double y, double z);

};


/**
 * A bummap is a map which contains a displacement vector for each spatial point.
 * That vector is a perturbation for the normal vector of a surface.
 * It can be either a procedural perturbation, or it can be loaded from a file.
 * @todo Perturbation loaded from a file.
 */
class Bumpmap
{
    public:
        /**
         * A bumpmap : perturbate the normal of an object.
         * @param level @f$ \in [0,1] @f$ if 1, the previous normal of the objet dose not remain any more;
         * if 0, no perturbation
         */
        Bumpmap(double _level) : level(_level) {}
        /** Default destructor */
        virtual ~Bumpmap() {};

        /**
         * A vector to add to the normal (and normalize the sum).
         */
        virtual const vector pertubation(const Point& p) = 0;

        const vector normal(const Point& p, const vector& norm);
    private:
        double level;
};

/**
 * A bumpmap using simplex noise.
 */
class ProceduralBumpmap : public Bumpmap
{
    private:
        double persist;
        int octa;

        double scale;

        double noise(double x, double y, double z);
    public:
    /**
     * Create a procedural bumpmap using Simplex Noise :
     *
     * @f$ bruit_i(v) = p^{i-1} \times bruit(2^i \times v) @f$
     * et @f$ bruitTotal = \sum_i^{nbOctaves} bruit_i(v) @f$
     * @param persistance @f$ \in [0,1] @f$
     * @param octaves
     */
    ProceduralBumpmap(double level, double persistance, int octaves);

    ~ProceduralBumpmap() {};


    const vector perturbation(const Point&p);
};


}


#endif // BUMPMAP_H
