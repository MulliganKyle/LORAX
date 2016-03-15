##################################################
#Friday, 16.January.2015 made by Lars C. Schwensen#
##################################################

#################################################################
#This is a standard makefile to compile C++ sourcecode on BBB   #
#Device: BeagleBone Black Rev. C1                               #
#OS: Debian                                                     #
#################################################################

OUTPUTNAME=I2Cdemo

#all the project files
#REPLACE THESE FILES WITH YOUR PROJECT FILES!!!!
PRJSRC=main.cpp i2c.cpp

#project files as .o files
OBJECTS= $(PRJSRC:.c=.o)

#additional includes
INCLUDES=
LIBRARIES=
#optimization level between (s0 (zero) and s3 (maximum))
OPTIMIZE=s

#compiler
CC=g++

#compilerflags
CFLAGS=-c -Wall

#linkerflags
LDFLAGS=

all: $(PRJSRC) $(OUTPUTNAME)

clean:
	 -rm -f *.o *.d
	 -rm -f I2Cdemo

$(OUTPUTNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
