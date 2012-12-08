export SRC=src
export BIN=bin
export PROG_NAME=main
export DOC=doc
export MAKE = make
export MRPROPER = make mrproper
export MASTER=..#Le chemin du Makefile par rapport au makefile appelé

all:
	cd $(SRC); $(MAKE) 4sphere; mv main $(MASTER)/$(BIN)/4sphere; $(MAKE) trans; mv main $(MASTER)/$(BIN)/trans; $(MAKE) manys; mv main $(MASTER)/$(BIN)/manys;

run:
	cd $(BIN); ./4sphere && ./trans && ./manys;

doc:
	doxygen

mrproper:
	cd $(SRC); $(MRPROPER)
	rm -R ./$(BIN)
	mkdir $(BIN)

.PHONY: run doc mrproper
