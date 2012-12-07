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


#define NB_SPHERES 20

int main(int argc, char** argv)
{
    rt::screen s(640,480);

    Real_Transparence scene;


    std::cout << "Nombre de param : " << argc << std::endl;

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
