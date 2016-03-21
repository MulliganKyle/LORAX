//####################################################
//#Saturday, 17.Januar.2015 made by Lars C. Schwensen#
//####################################################

//#################################################################
//#This file handles the UART functionality                       #
//#DEVICE: BeagleBone Black                                       #
//#OS: Debian                                                     #
//#################################################################

//UART.cpp

#ifndef BB_DEBUG_UART_H_
#define BB_DEBUG_UART_H_

#include <termios.h> //linux.die.net/man/3/termios
#include <stdint.h> //uint8_t
#include <stdio.h>
#include <string>

#define BAUD B9600
#define SELECTED_UART "BB-UART4"
#define ENABLE_PATH "/sys/devices/bone_capemgr.9/slots"

#define UART_PATH "/dev/ttyO4"

class UART {
   public:
      UART();
      virtual ~UART();

      int initUart();

      void sendChar(uint8_t character);

      void sendLine(std::string line);

      uint8_t receiveChar();

      std::string receiveLineString();
      std::string receiveLineData(std::string);

   private:
      int fd;

      int openDevice();
      void closeDevice();

      int writeTo(char target[], char value[]);
};

#endif /* BB_DEBUG_UART_H_ */
