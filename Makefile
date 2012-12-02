export SRC=src
export BIN=bin
export PROG_NAME=ptRT
export DOC=doc
export MAKE = make
export MRPROPER = make mrproper
export MASTER=..#Le chemin du Makefile par rapport au makefile appelé

#Il faudra modifier le Makefile dans source pour qu'il mette les binaires dans BIN
all:
	cd $(SRC); $(MAKE); mv main ../$(BIN)/;

run:
	cd $(BIN); ./$(PROG_NAME);

doc:
	doxygen

mrproper:
	cd $(SRC); $(MRPROPER)
