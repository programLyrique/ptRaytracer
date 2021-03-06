#include "bumpmap.h"

#include <cmath>

#include <iostream>

#include <cstdlib>

namespace rt
{

const vector SimplexNoise::grad3[12] =
{
    vector(1,1,0),vector(-1,1,0),vector(1,-1,0),vector(-1,-1,0),vector(1,0,1),
    vector(-1,0,1),vector(1,0,-1),vector(-1,0,-1),vector(0,1,1),vector(0,-1,1),
    vector(0,1,-1),vector(0,-1,-1)
};

const int SimplexNoise::p[256] = {151,160,137,91,90,15,
            131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
            190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
            88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
            77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
            102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
            135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
            5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
            223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
            129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
            251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
            49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

int SimplexNoise::perm[512]= {0};
int SimplexNoise::permMod12[512] = {0};

bool SimplexNoise::isInit = false;

void SimplexNoise::init()
{
    for ( int i = 0; i < 512; ++i )
    {
        perm[i] = p[i & 255];
        permMod12[i] = perm[i] % 12;
    }
}

double SimplexNoise::noise(const Point& p)
{
    double x = p.getX();
    double y = p.getY();
    double z = p.getZ();
    return noise(x, y, z);
}

double SimplexNoise::noise(double x, double y, double z)
{

//    if(!isInit)
//    {
//        std::cerr << "Init" << std::endl;
//        init();
//        isInit = true;
//    }

    double n0, n1, n2, n3; //Niveau de bruit aux quatre coins du simplexe (en 3D, le tétrahèdre).

    //Déterminer dans quel cellule de simplexe on se trouve :
    const double F3 = 1.0 / 3.0;
    double s = (x + y + z) * F3; // facteur de l'affinité

    int i = fastfloor(x + s);
    int j = fastfloor(y + s);
    int k = fastfloor(z + s);

//    int i = std::floor(x + s);
//    int j = std::floor(y + s);
//    int z = std::floor( z + s);

    const double G3 = 1.0 / 6.0; // Revenir dans l'espace non modifié
    double t = (i + j + k) * G3;
    // Distances à la cellule
    double X0  = i - t;
    double Y0 = j - t;
    double Z0 = k - t;
    double x0 = x - X0;
    double y0 = y - Y0;
    double z0 = z - Z0;


    //std::cerr << "x0 y 0 z0 : " << x0 << " " << y0 << " " << z0 << std::endl;


    // Dans quel simplexe :
    int i1, j1, k1;// coordonnées du second sommet du tétrahèdre
    int i2, j2, k2;// - du troisième (dans la "grille" en i,j,k)

    if(x0>=y0)
    {
        if(y0>=z0)
            { i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; } // X Y Z order
        else if(x0>=z0)
            { i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; } // X Z Y order
        else
            { i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; } // Z X Y order
    }
    else
    { // x0<y0
        if(y0<z0)
            { i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; } // Z Y X order
        else if(x0<z0)
            { i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; } // Y Z X order
        else
            { i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; } // Y X Z order
    }


    double x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    double y1 = y0 - j1 + G3;
    double z1 = z0 - k1 + G3;
    double x2 = x0 - i2 + 2.0*G3; // Offsets for third corner in (x,y,z) coords
    double y2 = y0 - j2 + 2.0*G3;
    double z2 = z0 - k2 + 2.0*G3;
    double x3 = x0 - 1.0 + 3.0*G3; // Offsets for last corner in (x,y,z) coords
    double y3 = y0 - 1.0 + 3.0*G3;
    double z3 = z0 - 1.0 + 3.0*G3;

    // On utilise la table des permutations
    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;
    int gi0 = permMod12[ii+perm[jj+perm[kk]]];
    int gi1 = permMod12[ii+i1+perm[jj+j1+perm[kk+k1]]];
    int gi2 = permMod12[ii+i2+perm[jj+j2+perm[kk+k2]]];
    int gi3 = permMod12[ii+1+perm[jj+1+perm[kk+1]]];

    // Contribution des 4 sommets du tétrahèdre
    double t0 = 0.5 - x0*x0 - y0*y0 - z0*z0;
    if(t0<0)
        n0 = 0.0;
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * (grad3[gi0] | vector(x0, y0, z0));
    }

    double t1 = 0.5 - x1*x1 - y1*y1 - z1*z1;
    if(t1<0)
        n1 = 0.0;
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * (grad3[gi1] | vector(x1, y1, z1));
    }

    double t2 = 0.5 - x2*x2 - y2*y2 - z2*z2;
    if(t2<0)
        n2 = 0.0;
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * (grad3[gi2] | vector(x2, y2, z2));
    }

    double t3 = 0.5 - x3*x3 - y3*y3 - z3*z3;
    if(t3<0)
        n3 = 0.0;
    else
    {
        t3 *= t3;
        n3 = t3 * t3 * (grad3[gi3] | vector(x3, y3, z3));
    }

    //std::cerr << "t0 t1 t2 t3 : " << t0 << " " << t1 << " " << t2 << " " << t3 << std::endl;
    // Pour obtenir la valeur finale fu bruit : on additionne les contributions, et envoie le tout dans l'intervalle [-1, 1]
    return 32.0 * (n0 + n1 + n2 + n3);
}

vector Bumpmap::normal(const Point& p, const vector& norm) const
{
    if(level == 0)
        return norm;
    vector perturb = this->perturbation(p);
    double resX = (1-level) * norm.x + level * perturb.x;
    double resY =  (1 - level) * norm.y + level * perturb.y;
    double resZ =  (1 - level) * norm.z + level * perturb.z;
    return vector(resX, resY, resZ).unit();
}

ProceduralBumpmap::ProceduralBumpmap(double level, double persistance, int octaves, double precision) :
Bumpmap(level), persist(persistance), octa(octaves), precis(precision)
{
    if(persist == 1)
        scale = octa;
    else
        scale = (1.0 - std::pow(persist, octa)) / ( 1.0 - persist);
}


double ProceduralBumpmap::noise(double x, double y, double z) const
{
    double sum = 0;
    double powerP = 1;
    double x0 = x;
    double y0 = y;
    double z0 = z;

    for(int i = 1 ; i <= octa; i++)
    {
        sum += powerP * SimplexNoise::noise(x0, y0, z0);
        powerP *= persist;
        x0 *= 2;
        y0 *= 2;
        z0 *= 2;
    }
    return  sum / scale;
}

vector ProceduralBumpmap::perturbation(const Point& p) const
{
//    double x = 0.1 * p.getX();
//    double y = 0.1 * p.getY();
//    double z = 0.1 * p.getZ();

      double x = precis * p.getX();
      double y = precis *p.getY();
      double z = precis * p.getZ();

//    double pertX = noise(x, y, z);
//    double pertY = noise(y, z, x);
//    double pertZ = noise(z, x, y);

    const double epsilon = 0.001;

    double pertX = noise(x - epsilon, y ,z) - noise(x + epsilon, y, z);
    double pertY = noise(x, y - epsilon, z) - noise(x , y + epsilon, z);
    double pertZ = noise(x, y, z - epsilon) - noise(x, y, z + epsilon);

    return vector(pertX, pertY, pertZ);

}


}
