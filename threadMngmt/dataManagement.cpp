//Data Management Thread
#include "dataManagement.hpp"


void dataManagement()
{

   /////////////////////////////
   //Globals used by query thread
   extern int curSpeed;
   extern int curRPM;
   extern int initFuel, curFuel;
   extern int initDist, curDist;
   extern int curTemp;
   extern int leftDist, rightDist;

   //Time Globals
   extern struct tm *curTime;

   //Initialization and Control Globals
   extern int speedLimit;
   extern bool forwardMode;
   extern bool englishUnits;

   //Data Management Globals
   extern int speedData;
   extern int RPMdata;
   extern int tempData;
   extern int rearData;
   extern float tankSizeLiters;
   extern float tankSizeGallons;
   //float fuelUsed;
   extern float fuelEcon;
   //float distTravelled;

   /////////////////////////////



   float fuelUsed;
   float distTravelled;
   float speedMiles;
   float tempF;
   float distTravelledMiles;
   std::fstream log;
   std::string timeStr;

   bool overSpeed=0;



   while(1)
   {
      if(!englishUnits)
      {
	 //set speed data
	 speedData=curSpeed;
	 usleep(10000);
	 //calculate the actual RPM
	 RPMdata=curRPM/4;
	 usleep(10000);

	 //calculate the actual engine temperature
	 tempData=curTemp-40;
	 usleep(10000);

	 //calculate the distance travelled
	 distTravelled=curDist-initDist;

	 //caluclate how much fuel has been used
	 fuelUsed=( (((float)initFuel*100)/255)-(((float)curFuel*100)/255))*tankSizeLiters;

	 //calculate fuel economy
	 fuelEcon=(fuelUsed/distTravelled)*100;
	 usleep(10000);


	 //determine which rear distance is closer
	 if(leftDist==0 && rightDist==0)
	 {
	    //if there was no data read by the sensors
	    //this means there was no object within range
	    //so set rear data to a large number so the GUI
	    //will know to say something like no objects detected
	    rearData=-1;
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
	 usleep(10000);


	 //if speed > 49 KPH and distance in rear is < 457 cm ~= 15ft
	 //data log for tailgating
	 if(speedData>49 && rearData<457)
	 {

	 }

	 //if speed > the user set speed limit
	 //activate audio script and data log
	 if(speedData>speedLimit && !overSpeed)
	 {
	    overSpeed=1;

	    log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);
	    timeStr=asctime(curTime);
	    timeStr.erase(timeStr.end());
	    log << timeStr << " ";
	    log << "Speed limit exceeded." << std::endl;

	    log.close();

	 }
	 else if(speedData<speedLimit && overSpeed)
	 {
	    overSpeed=0;

	    log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);
	    timeStr=asctime(curTime);
	    timeStr.erase(timeStr.end());
	    log << timeStr << " ";
	    log << "Speed limit no longer exceeded." << std::endl;

	    log.close();
	 }
	 usleep(10000);


      }

      else
      {
	 //convert speed
	 speedMiles= ((float)curSpeed*5)/8;
	 speedData= (int)(speedMiles+0.5);
	 usleep(10000);

	 //calculate the actual RPM
	 RPMdata=curRPM/4;
	 usleep(10000);

	 //convert temperature
	 tempF=((((float)(curTemp-40))*9)/5)+32;
	 tempData=(int)(tempF+0.5);
	 usleep(10000);

	 //convert fuel economy
	 distTravelled=curDist-initDist;
	 distTravelledMiles=(distTravelled*5)/8;
	 fuelUsed=( (((float)initFuel*100)/255)-(((float)curFuel*100)/255))*tankSizeGallons;
	 usleep(10000);
	 //calculate the actual RPM
	 RPMdata=curRPM/4;

	 fuelEcon=(fuelUsed/distTravelled)*100;
	 usleep(10000);

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
	 usleep(10000);


	 //if speed > 49 KPH and distance in rear is < 457 cm ~= 15ft
	 //data log for tailgating
	 if(speedData>30 && rearData<180)
	 {

	 }

	 //if speed > the user set speed limit
	 //activate audio script and data log
	 if(speedData>speedLimit && !overSpeed)
	 {
	    overSpeed=1;

	    log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);
	    timeStr=asctime(curTime);
	    timeStr.erase(timeStr.end());
	    log << timeStr << " ";
	    log << "Speed limit exceeded." << std::endl;

	    log.close();

	 }
	 else if(speedData<speedLimit && overSpeed)
	 {
	    overSpeed=0;

	    log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);
	    timeStr=asctime(curTime);
	    timeStr.erase(timeStr.end());
	    log << timeStr << " ";
	    log << "Speed limit no longer exceeded." << std::endl;

	    log.close();
	 }
	 usleep(10000);
      }
   }
}
