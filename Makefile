export SRC=src
export BIN=bin
export PROG_NAME=main
export DOC=doc
export MAKE = make
export MRPROPER = make mrproper
export MASTER=..#Le chemin du Makefile par rapport au makefile appelé

all:
	cd $(SRC); $(MAKE); mv main $(MASTER)/$(BIN)/;

run:
	cd $(BIN); ./$(PROG_NAME);

doc:
	doxygen

mrproper:
	cd $(SRC); $(MRPROPER)

.PHONY: run doc mrproper
