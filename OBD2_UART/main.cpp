
#include "UART.h"
#include <ctime>
#include <stdint.h>
#include <iostream>

volatile int i;

int trash(int count)
{
   for(i=0; i<100000000; i++)
   {
      if(i >= count)
      {
	 return i;
      }
   }
   return i;
}

int main()
{
   UART uart;

   std::string outputString;

   uart.initUart();

   std::string RPM="010C\r";
   std::string Speed="010D\r";
   
   uart.sendLine("ATZ\r");
   
   trash(100000000);

   outputString = uart.receiveLineString();
   std::cout << outputString << std::endl;

   uart.sendLine(RPM);
//   trash(50000000);

   outputString = uart.receiveLineData("010C41 0C");

   std::cout << outputString << std::endl;

   //return 1;
}
