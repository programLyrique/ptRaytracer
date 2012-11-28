#include <iostream>
#include <unistd.h>
#include "screen.hpp"
#include "scene.h"



int main(void)
{
	rt::screen s(640,480);

	// here the code to draw the pixels...
	Scene scene();
	
	

	while(s.update()) {
		scene.render(&s);
	}

	return 0;
}
