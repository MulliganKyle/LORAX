INCLUDE_DIRS = -I/mnt/SD/local/include 
LIB_DIRS = 
CC=g++

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lrt
CPPLIBS= -L/mnt/SD/local/lib -lopencv_core -lopencv_flann -lopencv_video -lopencv_videoio -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs 

HFILES= 
CFILES= 
CPPFILES= obd2gui.cpp

SRCS= ${HFILES} ${CFILES}
CPPOBJS= ${CPPFILES:.cpp=.o}

all:	obd2gui 

clean:
	-rm -f *.o *.d
	-rm -f capture

distclean:
	-rm -f *.o *.d

obd2gui: obd2gui.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o `pkg-config --libs opencv` $(CPPLIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) -c $<
