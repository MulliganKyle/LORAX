
#include "UART.h"
#include "i2c.h"
#include <ctime>
#include <stdint.h>
#include <iostream>
#include <string>
#include <time.h>

#define DEVICE_ADDR0 0x70
#define DEVICE_ADDR1 0x71




int main()
{
   UART uart;
//   myI2C *sensorPtr0 = new myI2C();
//   myI2C *sensorPtr1 = new myI2C();
   

   std::string outputString;
   int outData;
  
   //Globals at some point
   //===============================
   int curSpeed;
   int curRPM;
   int initFuel, prevFuel, curFuel;
   int initDist, curDist;
   int curTemp;
   time_t rawTime;
   struct tm *prevTime, *curTime;
   int timeOffset=-7;
   int leftDist, rightDist;
   bool mode=1;
   //===============================

   std::string RPM="010C\r";
   std::string Speed="010D\r";
   std::string Temp="0105\r";
   std::string Fuel="012F\r";
   std::string Dist="0131\r";

//   sensorPtr0->i2cSetAddress(DEVICE_ADDR0);
//   sensorPtr1->i2cSetAddress(DEVICE_ADDR1);

   uart.initUart();

   uart.sendLine("ATZ\r");


   usleep(5000000);
   outputString = uart.receiveLineString();
   std::cout << outputString << std::endl;

#if 1
   

   //Get initial Distance
   //======================================
   uart.sendLine(Dist);
   initDist=uart.receiveLineData("013141 31 ",5);
   curDist=initDist;
   //======================================
std::cout << "dist: " << curDist << std::endl;

   //Get initial time
   //======================================
   time(&rawTime);
   prevTime=localtime(&rawTime);
   prevTime->tm_hour+=timeOffset;
   curTime=localtime(&rawTime);
   curTime->tm_hour+=timeOffset;
   //======================================
usleep(500000);
   //Get initial fuel level
   //======================================
   uart.sendLine(Fuel);
   initFuel=uart.receiveLineData("012F41 2F ",2);
   prevFuel=initFuel;
   curFuel=initFuel;
   //======================================
std::cout << "fuel: " << curFuel << std::endl;

   while(1)
   {
      //Forward Mode
      //======================================
      if(mode)
      {

usleep(500000);
	 //Query for Speed
	 //======================================
	 uart.sendLine(Speed);
	 curSpeed=uart.receiveLineData("010D41 0D ",2);
	 //======================================

usleep(500000);
	 //Query for RPM
	 //======================================
	 uart.sendLine(RPM);
	 curRPM=uart.receiveLineData("010C41 0C ",5);
	 //======================================
	 
usleep(500000);
	 //Query for Engine Temp
	 //======================================
	 uart.sendLine(Temp);
	 curTemp=uart.receiveLineData("010541 05 ",2);
	 //======================================
	 
	 //Get the time
	 //======================================
	 time(&rawTime);
	 curTime=localtime(&rawTime);
	 curTime->tm_hour+=timeOffset;
	 //======================================

usleep(500000);
	 //if it's been a minute, check fuel level
	 //======================================
	 if(curTime->tm_min!=prevTime->tm_min)
	 {
	    prevTime=localtime(&rawTime);
	    prevTime->tm_hour+=timeOffset;
	    uart.sendLine(Fuel);
	    curFuel=uart.receiveLineData("012F41 2F ",2);
	 }
	 //======================================
	 
usleep(500000);
	 //if the fuel level has changed,
	 //check distance
	 //======================================
	 if(prevFuel!=curFuel)
	 {
	    prevFuel=curFuel;
	    uart.sendLine(Dist);
	    curDist=uart.receiveLineData("013141 31 ",4);
	 }

	 //if the speed is greater than 30MPH or 49 KPH
	 //check rear distance
	 //======================================
	 if(curSpeed > 49)
	 {
	    //sensorPtr0->Send_I2C_Byte(0x00, 0x51);
	    //usleep(68E3);
	    //leftDist=sensorPtr0->Read_2I2C_Bytes(0x02);
	    //sensorPtr1->Send_I2C_Byte(0x00, 0x51);
	    //usleep(68E3);
	    //rightDist=sensorPtr1->Read_2I2C_Bytes(0x02);
	 }
	 //======================================

      }
      //======================================

      //Reverse Mode
      //======================================
      else
      {
	 //Query reverse distance as much as possible
	 //======================================
	 //sensorPtr0->Send_I2C_Byte(0x00, 0x51);
	 //usleep(68E3);
	 //leftDist=sensorPtr0->Read_2I2C_Bytes(0x02);
	 //sensorPtr1->Send_I2C_Byte(0x00, 0x51);
	 //usleep(68E3);
	 //rightDist=sensorPtr1->Read_2I2C_Bytes(0x02);
	 //======================================

      }
   std::cout << "speed: " << curSpeed;
   std::cout << " RPM: " << curRPM/4;
   std::cout << " Temp: " << curTemp-40;
   std::cout << asctime(curTime) << "\r"; 

   }




#endif


#if 0
   outputString = uart.receiveLineString();
   std::cout << outputString << std::endl;

   uart.sendLine(RPM);
   std::cout << "here 1" << std::endl;
   usleep(5000000);
//   outputString = uart.receiveLineString();
//   std::cout << outputString << std::endl;

   outData = uart.receiveLineData("010C41 0C ", 5);

   std::cout << outData << std::endl;
#endif

}
