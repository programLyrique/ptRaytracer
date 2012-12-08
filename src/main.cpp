#include <iostream>
#include <unistd.h>
#include <ctime>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"
#include "ptScenes.h"



int main()
{
    rt::screen s(640,480);

	// here the code to draw the pixels...
    Four_Spheres scene;

    std::cout << "Starting rendering." << std::endl;

    time_t beginning = std::time(NULL);

    scene.render(s);

    time_t end = std::time(NULL);

    std::cout << "End of rendering. Took : " << end - beginning << " seconds." << std::endl;

    while(s.update()) {

    }


    return 0;
}
