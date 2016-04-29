// Mock query driver

#include "mockQuery.hpp"

void mockQuery()
{
   extern int curSpeed;
   extern int curTemp;
   extern int speedData;
   extern bool forwardMode;
   int modify=1;

   while(1)
   {
      curSpeed+=modify;

      if(curSpeed>50||curSpeed<1)
      {
	 modify=modify*-1;
      }

      usleep(500000);

      curTemp+=2*modify;

      usleep(500000);

      if(curSpeed<8)
      {
	 forwardMode=0;
      }
      else
      {
	 forwardMode=0;
      }

   }


}
