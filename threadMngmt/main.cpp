//#includes===================

#include <ctime>
#include <stdint.h>
#include <iostream>
#include <string>
#include <time.h>
#include "UART.h"
#include "i2c.h"
#include <stdio.h>
#include <thread>


#include "GUI.hpp"
#include "dataManagement.hpp"
#include "query.hpp"
//============================

//Globals=====================

//Globals used by query thread
int curSpeed;
int curRPM;
int initFuel, prevFuel, curFuel;
int initDist, curDist;
int curTemp;
int leftDist, rightDist;

//Time Globals
time_t rawTime;
struct tm *prevTime, *curTime;

//Initialization and Control Globals
int timeOffset;
int speedLimit;
bool forwardMode;
bool englishUnits;

//Data Management Globals
int speedData;
int RPMdata;
int tempData;
int rearData;
float tankSizeLiters;
float tankSizeGallons;
//float fuelUsed;
float fuelEcon;
//float distTravelled;

//============================

int main(int argc, char** argv)
{
   
   //Spawn GUI thread
   std::thread GUI_thread (GUI);

   //Spawn query thread
   std::thread query_thread (query);
   
   //Spawn data management thread
   std::thread dataManagement_thread (dataManagement);



   //synchronize threads:
   GUI_thread.join();
   query_thread.join();
   dataManagement_thread.join();
}
