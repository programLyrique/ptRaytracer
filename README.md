ptRaytracer
===========

A raytracer.

You need the SDL and the posix thread library to compile the raytracer. 
The makefile will build three example programs.

Building :

make

Warning : don't do make -jx where x > 1. Some examples will not compile in this case.

Running the three examples, one by one :

make run

To go to the next example, close the window or hit ctrl+c in the terminal.

Building the doc :

make doc

To read it : yourInternetNavigator doc/html.index.html