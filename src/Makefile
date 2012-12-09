CC=g++
CFLAGS=-W -Wall -g -ansi -pedantic -pthread #-O3
LDFLAGS=

INCLUDE=-I. -I/usr/include -I/usr/include/SDL -I./include
LIBS=-L/usr/lib -lSDL -lpthread

EXEC=$(PROG_NAME)
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
PROG_NAME=main

CFLAGS+=-DFOUR_SPHERES_REFLEXIONS
#4sphere: CFLAGS+=-DFOUR_SPHERES_REFLEXIONS
#4sphere: clean $(EXEC)


#trans: CFLAGS+=-DREAL_TRANSPARENCE
#trans: clean $(EXEC)


#manys: CFLAGS+=-DMANY_SPHERES
#manys: clean $(EXEC)

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
