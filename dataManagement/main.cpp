
#include <ctime>
#include <stdint.h>
#include <iostream>
#include <string>
#include <time.h>





int main()
{
   int curSpeed;
   int curRPM;
   int initFuel, prevFuel, curFuel;
   int initDist, curDist;
   int curTemp;
   time_t rawTime;
   struct tm *prevTime, *curTime;
   int timeOffset=-7;
   int leftDist, rightDist;
   bool mode;


   int RPMdata;
   int tempData;
   float tankSizeLiters;
   float fuelUsed;
   float fuelEcon;
   float distTravelled;



   while(1)
   {
      //calculate the actual RPM
      RPMdata=curRPM/4;

      //calculate the actual engine temperature
      tempData=curTemp-40;

      //calculate the distance travelled
      distTravelled=curDist-initDist;

      //caluclate how much fuel has been used
      fuelUsed=( (((float)initFuel*100)/255)-(((float)curFuel*100)/255))*tankSizeLiters;

      //calculate fuel economy
      fuelEcon=(fuelUsed/distTravelled)*100;




}
