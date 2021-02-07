
# Makefile created by Raphael 
# source: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
 
 # type "make" to compile the project. Name of the executable: rpg_game
 # type "make .PHONY" to clean the project
 # Makefile has to be located in ../src directory
 # sourcefiles are located in ../src
 # obj-file are located in ../src/obj
 # header files are located in ../include
 # libraries are located in ../lib

# *****************************************************
# Variables to control Makefile operation

IDIR =../include
CC = g++ -std=c++17 -pg
CFLAGS =-I$(IDIR)

ODIR=build
LDIR =../lib

LIBS=-lm

_DEPS = Enemy.h Player.h Screen.h Trainee.h Mage.h Fighter.h TestBot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Player.o Screen.o Enemy.o Trainee.o Mage.o Fighter.o TestBot.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
 
# ****************************************************

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(ODIR)/rpg_game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
