#################################################################
#This is a standard makefile to compile C++ sourcecode on BBB   #
#Device: BeagleBone Black Rev. C1                               #
#OS: Debian                                                     #
#################################################################

OUTPUTNAME=OBD2demo

#all the project files
#REPLACE THESE FILES WITH YOUR PROJECT FILES!!!!
PRJSRC=main.cpp UART.cpp i2c.cpp

#project files as .o files
OBJECTS= $(PRJSRC:.cpp=.o)

#additional includes
INCLUDES=
LIBRARIES=
#optimization level between (s0 (zero) and s3 (maximum))
OPTIMIZE=s

#compiler
CC=g++

#compilerflags
CFLAGS=-c -Wall -std=c++0x ` pkg-config glib-2.0  --cflags --libs`

#linkerflags
LDFLAGS=` pkg-config glib-2.0  --cflags --libs`

all: $(PRJSRC) $(OUTPUTNAME)

clean:
	 -rm -f *.o *.d
	 -rm -f OBD2demo

$(OUTPUTNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
