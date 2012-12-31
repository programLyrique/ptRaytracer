export SRC=src
export BIN=bin
export PROG_NAME=main
export DOC=doc
export MAKE = make
export MRPROPER = make mrproper
export MASTER=..#Le chemin du Makefile par rapport au makefile appelé

all:
	cd $(SRC); $(MAKE); mv main $(MASTER)/$(BIN)/real_transparence
	#$(MAKE) trans; mv main $(MASTER)/$(BIN)/trans; $(MAKE) manys; mv main $(MASTER)/$(BIN)/manys;

run:
	cd $(BIN); ./real_transparence

doc:
	doxygen

mrproper:
	cd $(SRC); $(MRPROPER)
	rm -R ./$(BIN)
	mkdir $(BIN)

.PHONY: run doc mrproper
