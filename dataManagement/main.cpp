#include <fstream>
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
   bool englishUnits=0;
   int speedLimit;

   int RPMdata;
   int tempData;
   int speedData;
   int rearData;
   float tankSizeLiters;
   float tankSizeGallons;
   float fuelEcon;

   //these are not globals
   float fuelUsed;
   float distTravelled;
   float speedMiles;
   float tempF;
   float distTravelledMiles;
   std::fstream log;
   std::string timeStr;



   while(1)
   {
      if(!englishUnits)
      {
	 //set speed data
	 speedData=curSpeed;

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


	 //determine which rear distance is closer
	 if(leftDist==0 && rightDist==0)
	 {
	    //if there was no data read by the sensors
	    //this means there was no object within range
	    //so set rear data to a large number so the GUI
	    //will know to say something like no objects detected
	    rearData=MAX_INT;
	 }
	 else
	 {
	    if(leftDist<rightDist)
	    {
	       rearData=leftDist;
	    }
	    else
	    {
	       rearData=rightDist;
	    }
	 }


	 //if speed > 49 KPH and distance in rear is < 457 cm ~= 15ft
	 //data log for tailgating
	 if(speedData>49 && rearData<457)
	 {

	 }

	 //if speed > the user set speed limit
	 //activate audio script and data log
	 if(speedData>speedLimit)
	 {
	    log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);
	    timeStr=asctime(curTime);
	    timeStr.erase(timeStr.end());
	    log << timeStr << " ";
	    log << "Speed limit exceeded." << std::endl;

	    log.close();

	 }

      }

      else
      {
	 //convert speed
	 speedMiles= ((float)curSpeed*5)/8;
	 speedData= (int)(speedMiles+0.5);

	 //calculate the actual RPM
	 RPMdata=curRPM/4;

	 //convert temperature
	 tempF=((((float)(curTemp-40))*9)/5)+32;
	 tempData=(int)(tempF+0.5);

	 //convert fuel economy
	 distTravelled=curDist-initDist;
	 distTravelledMiles=(distTravelled*5)/8;
	 fuelUsed=( (((float)initFuel*100)/255)-(((float)curFuel*100)/255))*tankSizeGallons;
	 fuelEcon=(fuelUsed/distTravelled)*100;

	 //determine which rear distance is closer
	 if(leftDist==0 && rightDist==0)
	 {
	    //if there was no data read by the sensors
	    //this means there was no object within range
	    //so set rear data to a large number so the GUI
	    //will know to say something like no objects detected
	    rearData=100000;
	 }
	 else
	 {
	    //convert rear distance
	    if(leftDist<rightDist)
	    {
	       rearData=(leftDist*3937)/10000;
	    }
	    else
	    {
	       rearData=(rightDist*3937)/10000;
	    }
	 }


	 //if speed > 49 KPH and distance in rear is < 457 cm ~= 15ft
	 //data log for tailgating
	 if(speedData>30 && rearData<180)
	 {

	 }

	 //if speed > the user set speed limit
	 //activate audio script and data log
	 if(speedData>speedLimit)
	 {
	    log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);
	    timeStr=asctime(curTime);
	    timeStr.erase(timeStr.end());
	    log << timeStr << " ";
	    log << "Speed limit exceeded." << std::endl;

	    log.close();

	 }
      }
   }
}
