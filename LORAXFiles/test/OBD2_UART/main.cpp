
#include "UART.h"
#include <ctime>
#include <stdint.h>
#include <iostream>

int main()
{
   UART uart;

   std::string outputString;
   int outData;
   uart.initUart();

   std::string RPM="010C\r";
   std::string Speed="010D\r";
   
   uart.sendLine("ATZ\r");
  
   sleep(5);

   outputString = uart.receiveLineString();
   std::cout << outputString << std::endl;

   uart.sendLine(RPM);


   outData = uart.receiveLineData("010C41 0C ", 5);

   std::cout << outData << std::endl;

}
