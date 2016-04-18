#################################################################
#This is a standard makefile to compile C++ sourcecode on BBB   #
#Device: BeagleBone Black Rev. C1                               #
#OS: Debian                                                     #
#################################################################

INCLUDE_DIRS = -I/mnt/SD/local/include 

OUTPUTNAME=OBD2demo

#all the project files
#REPLACE THESE FILES WITH YOUR PROJECT FILES!!!!
PRJSRC=main.cpp UART.cpp i2c.cpp GUI.cpp query.cpp dataManagement.cpp

#project files as .o files
OBJECTS= $(PRJSRC:.cpp=.o)

CPPLIBS= -L/mnt/SD/local/lib -lopencv_core -lopencv_flann -lopencv_video -lopencv_videoio -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

#additional includes
INCLUDES=
LIBRARIES=
#optimization level between (s0 (zero) and s3 (maximum))
OPTIMIZE=s

#compiler
CC=g++

#compilerflags
CFLAGS=-c -Wall -std=c++0x $(INCLUDE_DIRS) ` pkg-config glib-2.0  --cflags --libs`

#linkerflags
LDFLAGS=` pkg-config glib-2.0  --cflags --libs opencv` $(CPPLIBS)

all: $(PRJSRC) $(OUTPUTNAME)

clean:
	 -rm -f *.o *.d
	 -rm -f OBD2demo

$(OUTPUTNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@