export SRC=src
export BIN=bin
export PROG_NAME=ptRT
export DOC=doc
export MASTER=..#Le chemin du Makefile par rapport au makefile appelé

#Il faudra modifier le Makefile dans source pour qu'il mette les binaires dans BIN
all:
    cd $(SRC)
    $(MAKE)

run:
    cd $(BIN)
    ./$(PROG_NAME)

doc:
