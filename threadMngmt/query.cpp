//Query thread
#include "query.hpp"


static gboolean onButtonEvent(GIOChannel *channel, GIOCondition condition, gpointer user_data)
{
   extern bool forwardMode;
   GError *error = 0;
   gsize bytes_read = 0; 
   const int buf_sz = 1024;
   gchar buf[buf_sz] = {};
   g_io_channel_seek_position( channel, 0, G_SEEK_SET, 0 );
   GIOStatus rc = g_io_channel_read_chars( channel,
	 buf, buf_sz - 1,
	 &bytes_read,
	 &error );

   forwardMode=(int)buf[0]-48;
   return 1;
}


void query()
{

   ////////////////////////////////////////////////
   extern int curSpeed;
   extern int curRPM;
   extern int initFuel, prevFuel, curFuel;
   extern int initDist, curDist;
   extern int curTemp;
   extern int leftDist, rightDist;

   //Time Globals
   extern time_t rawTime;
   extern struct tm *prevTime, *curTime;
   extern int timeOffset;
   extern bool forwardMode;



   ////////////////////////////////////////////////


   int temp, count=0;
   UART uart;
   myI2C *sensorPtr0 = new myI2C();
   myI2C *sensorPtr1 = new myI2C();

   std::string RPM="010C\r";
   std::string Speed="010D\r";
   std::string Temperature="0105\r";
   std::string Fuel="012F\r";
   std::string Dist="0131\r";

   //   sensorPtr0->i2cSetAddress(DEVICE_ADDR0);
   //   sensorPtr1->i2cSetAddress(DEVICE_ADDR1);

   uart.initUart();

   uart.sendLine("ATZ\r");

   int fd = open( "/sys/class/gpio/gpio67/value", O_RDONLY | O_NONBLOCK );
   GIOChannel* channel = g_io_channel_unix_new( fd );
   GIOCondition cond = GIOCondition( G_IO_PRI );
   guint id = g_io_add_watch( channel, cond, onButtonEvent, 0 );


   usleep(5000000);




   //Get initial Distance
   //======================================
   uart.sendLine(Dist);
   temp=-1;
   while(temp==-1)
   {
      if ((temp=uart.receiveLineData("013141 31 ",5))!=-1)
      {
	 initDist=temp;
	 curDist=initDist;
      }
      usleep(500000);
   }
   //======================================

   //Get initial time
   //======================================
   time(&rawTime);
   prevTime=localtime(&rawTime);
   prevTime->tm_hour+=timeOffset;
   curTime=localtime(&rawTime);
   curTime->tm_hour+=timeOffset;
   if(prevTime->tm_hour<0)
   {
      prevTime->tm_hour+=24;
      curTime->tm_hour+=24;
   }
   //======================================

   //Get initial fuel level
   //======================================
   uart.sendLine(Fuel);
   temp=-1;
   while(temp==-1)
   {
      if ((temp=uart.receiveLineData("012F41 2F ",2))!=-1)
      {
	 initFuel=temp;
	 prevFuel=initFuel;
	 curFuel=initFuel;
      }
      usleep(500000);
   }
   //======================================

   //Query for Engine Temp
   //======================================
   uart.sendLine(Temperature);
   temp=-1;
   while(temp==-1)
   {
      if ((temp=uart.receiveLineData("010541 05 ",2))!=-1)
      {
	 curTemp=temp;
      }
      usleep(500000);
   }
   //======================================

   while(1)
   {
      //Forward Mode
      //======================================
      if(forwardMode)
      {

	 //Query for Speed
	 //======================================
	 uart.sendLine(Speed);
	 if ((temp=uart.receiveLineData("010D41 0D ",2))!=-1)
	 {
	    curSpeed=temp;
	 }
	 //======================================

	 usleep(500000);
	 //Query for RPM
	 //======================================
	 uart.sendLine(RPM);
	 if ((temp=uart.receiveLineData("010C41 0C ",5))!=-1)
	 {
	    curRPM=temp;
	 }
	 //======================================

	 //Get the time
	 //======================================
	 time(&rawTime);
	 curTime=localtime(&rawTime);
	 curTime->tm_hour+=timeOffset;
	 if(curTime->tm_hour < 0)
	 {
	    curTime->tm_hour+=24;
	 }
	 //======================================

	 usleep(500000);
	 //if it's been a minute, check fuel level and engine Temp
	 //======================================
	 if(count>99)
	 {
	    count=0;
	    prevTime=localtime(&rawTime);
	    prevTime->tm_hour+=timeOffset;
	    if(prevTime->tm_hour < 0)
	    {
	       prevTime->tm_hour+=24;
	    }
	    uart.sendLine(Fuel);
	    if ((temp=uart.receiveLineData("012F41 2F ",2))!=-1)
	    {
	       curFuel=temp;
	    }
	    usleep(500000);

	    //Query for Engine Temp
	    //======================================
	    if ((temp=uart.receiveLineData("010541 05 ",2))!=-1)
	    {
	       curTemp=temp;
	    }
	    //======================================
	    usleep(500000);
	 }
	 //======================================

	 //if the fuel level has changed,
	 //check distance
	 //======================================
	 if(prevFuel!=curFuel)
	 {
	    prevFuel=curFuel;
	    uart.sendLine(Dist);
	    if ((temp=uart.receiveLineData("013141 31 ",4))!=-1)
	    {
	       curDist=temp;
	    }
	    usleep(500000);
	 }

	 //if the speed is greater than 30MPH or 49 KPH
	 //check rear distance
	 //======================================
	 if(curSpeed > 49)
	 {
	    /*sensorPtr0->Send_I2C_Byte(0x00, 0x51);
	      usleep(68E3);
	      leftDist=sensorPtr0->Read_2I2C_Bytes(0x02);
	      sensorPtr1->Send_I2C_Byte(0x00, 0x51);
	      usleep(68E3);
	      rightDist=sensorPtr1->Read_2I2C_Bytes(0x02);*/
	 }
	 //======================================
      
      count++;

      }
      //======================================

      //Reverse Mode
      //======================================
      else
      {
	 usleep(1000000);
	 //Query reverse distance as much as possible
	 //======================================
	 /*sensorPtr0->Send_I2C_Byte(0x00, 0x51);
	   usleep(68E3);
	   leftDist=sensorPtr0->Read_2I2C_Bytes(0x02);
	   sensorPtr1->Send_I2C_Byte(0x00, 0x51);
	   usleep(68E3);
	   rightDist=sensorPtr1->Read_2I2C_Bytes(0x02);*/
	 //======================================

      }
   }
}
