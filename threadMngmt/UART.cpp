//####################################################
//#Saturday, 17.Januar.2015 made by Lars C. Schwensen#
//####################################################

//#################################################################
//#This file handles the UART functionality                       #
//#DEVICE: BeagleBone Black                                       #
//#OS: Debian                                                     #
//#################################################################

//UART.cpp

#include "UART.h"

#include <fcntl.h> //handles O_RDWR etc.
#include <string.h> // needed for memset
#include <iostream>

#include <fstream>

UART::UART()
{
   char target[] = ENABLE_PATH;
   char value[] = SELECTED_UART;

   writeTo(target, value);
}

UART::~UART()
{
   closeDevice();
}

int UART::openDevice()
{
   const char *device = UART_PATH;
   fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);

   if(fd == -1) {
      printf("failed to open port!\n");
   }

   return fd;
}

void UART::closeDevice()
{
   close(fd);
}

int UART::initUart()
{
   struct termios settings;
   memset(&settings,0,sizeof(settings));

   settings.c_iflag = 0; //input flags
   settings.c_oflag = 0; //output flags
   settings.c_cflag=
      CS8 | //8 bits
      CREAD | //enable receiver
      CLOCAL; //ignore modem status lines
   settings.c_lflag=0;
   settings.c_cc[VMIN]=1; //minimum one value
   settings.c_cc[VTIME]=5; //time

   fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK); //blocking mode (does not really work)

   if(openDevice())
   {
      cfsetispeed(&settings,BAUD); //input baudrate
      cfsetospeed(&settings,BAUD); //output baudrate

      tcsetattr(fd,TCSANOW,&settings);
      return 1;
   }

   return -1;
}

void UART::sendChar(uint8_t character)
{
   write(fd,&character,1);
}

void UART::sendLine(std::string line)
{
   int length;
   length=line.size();
   int count;

   for(count=0; count<length; count++)
   {
      sendChar(line[count]);
   }
}
//
// This function converts the non-blocking read() function into a single-character blocking read
//
uint8_t UART::receiveChar()
{
   uint8_t character;

   while(read(fd, &character, 1) < 1);

   return character;
}

std::string UART::receiveLineString()
{
   char nextChar;
   std::string receivedString;
   
   while(read(fd, &nextChar, 1)==1)
   {
      if(nextChar !='\r')
      {
	 std::cout<< nextChar << std::endl;

	 receivedString+=nextChar;
      }
   }
   return receivedString;
}

int UART::receiveLineData(std::string command, int length)
{
   char nextChar;
   std::string receivedString;
   std::string dataStr;
   int data;
   bool commandFound=0;
   std::size_t found, noData;
   int count=0, stuckCount=0;

   while( !commandFound )
   {
      if(read(fd, &nextChar, 1)==1)
      {
	 if(nextChar != '\r')
	 {
	    receivedString+=nextChar;
	 }
      }
      found=receivedString.find(command);
      if(found!=std::string::npos)
      {
	 commandFound=1;
      }
      noData=receivedString.find("NO DATA");
      if(noData!=std::string::npos || stuckCount>1000000)
      {
	 return -1;
      }
      stuckCount++;
   }

   while(count<=length)
   {

      if(read(fd, &nextChar, 1)==1)
      {
	 dataStr+=nextChar;
	 count++;
      }
   }
   if(length>4)
   {
      dataStr.erase(2,1);
   }

   data = std::stoi(dataStr, NULL, 16);

   return data;
}


int UART::writeTo(char target[], char value[])
{
   std::ofstream targetFile;
   targetFile.open(target);
   if(targetFile.is_open())
   {
      targetFile << value;
      targetFile.close();
      return 1;
   }
   return -1;
}

