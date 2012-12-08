CC=g++
CFLAGS=-W -Wall -ansi -pedantic -O3 -DFOUR_SPHERES_REFLEXIONS
LDFLAGS=

INCLUDE=-I. -I/usr/include -I/usr/include/SDL -I./include
LIBS=-L/usr/lib -lSDL -lpthread

EXEC=$(PROG_NAME)
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)	
PROG_NAME=4sphere refraction manys

all: $(EXEC)

4sphere: 

refraction:

manys:

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
