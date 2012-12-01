CC=g++
CFLAGS=-W -Wall -ansi -pedantic -D_REENTRANT
LDFLAGS=

INCLUDE=-I. -I/usr/include -I/usr/include/SDL -I./include
LIBS=-L/usr/lib -lSDL -lpthreads

EXEC=main
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
