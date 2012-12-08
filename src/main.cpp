#include <iostream>
#include <unistd.h>
#include <cmath>
#include <sstream>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"
#include "plan.h"

#include "ptScenes.h"


/*
 * Pass -DNOM_SCENE to build the scene you want.
 * It can be necessary to do a make mrproper before.
 */

#ifdef MANY_SPHERES
// You can put 1000 here, but more is expected to be very long.
// For 1000, 373 s on a core i7, 2,6 GHz, 8 cores.
#define NB_SPHERES  1000
#endif


int main(int argc, char** argv)
{
    rt::screen s(640,480);
#if defined(REAL_TRANSPARENCE)
    Real_Transparence scene;
#elif defined(MANY_SPHERES)
    Many_Spheres scene(NB_SPHERES);
#elif defined(FOUR_SPHERES_REFLEXIONS)
    Four_Spheres_Reflexions scene;
#endif


    std::cout << "Number of param : " << argc << std::endl;

    //On peut passer le nombre de coeurs voulus en paramètre
    if(argc <= 1)
        scene.render(s);
    else
    {
        std::istringstream iss(argv[1]);
        // To prevent from format errors.
        iss.exceptions(std::istringstream::failbit | std::istringstream::badbit );
        int nbThreads;
        iss >> nbThreads;
        scene.render(s, nbThreads);
    }

    while(s.update()) {

    }

    return 0;
}
