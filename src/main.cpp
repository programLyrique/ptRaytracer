#include <iostream>
#include <unistd.h>

#include "screen.hpp"
#include "scene.h"
#include "color.hpp"
#include "texture.h"
#include "pointlight.h"
#include "ptScenes.h"
#include <cmath>
#include <sstream>


int main(int argc, char** argv)
{
    rt::screen s(640,480);

	// here the code to draw the pixels...
    Four_Spheres scene;

    scene.render(s);

    while(s.update()) {

    }

    return 0;
}
