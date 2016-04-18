#include <ctime>
#include <string>
#include <iostream>


int main()
{
   std::string timeText, dispText;
   time_t rawTime;
   struct tm *curTime;

   time(&rawTime);
   curTime=localtime(&rawTime);
   timeText=asctime(curTime);
   std::cout << timeText << std::endl;
   dispText = timeText.substr (11,5);
   std::cout << dispText << std::endl;
}
