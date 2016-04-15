//Query thread
#include "query.hpp"


static gboolean onButtonEvent(GIOChannel *channel,
			      GIOCondition condition,
			      gpointer user_data)
{
   std::cerr << "onButtonEvent" << std::endl;
   GError *error = 0;
   gsize bytes_read = 0; 
   const int buf_sz = 1024;
   gchar buf[buf_sz] = {};
   g_io_channel_seek_position( channel, 0, G_SEEK_SET, 0 );
   GIOStatus rc = g_io_channel_read_chars( channel,
	 buf, buf_sz - 1,
	 &bytes_read,
	 &error );
   std::cerr << "rc:" << rc << " data:" << buf << std::endl;

   // thank you, call again!
   return 1;
}


void query()
{
   UART uart;
   myI2C *sensorPtr0 = new myI2C();
   myI2C *sensorPtr1 = new myI2C();

   std::string RPM="010C\r";
   std::string Speed="010D\r";
   std::string Temp="0105\r";
   std::string Fuel="012F\r";
   std::string Dist="0131\r";

   sensorPtr0->i2cSetAddress(DEVICE_ADDR0);
   sensorPtr1->i2cSetAddress(DEVICE_ADDR1);

   uart.initUart();

   uart.sendLine("ATZ\r");

   int fd = open( "/sys/class/gpio/gpio67/value", O_RDONLY | O_NONBLOCK );
   GIOChannel* channel = g_io_channel_unix_new( fd );
   GIOCondition cond = GIOCondition( G_IO_PRI );
   guint id = g_io_add_watch( channel, cond, onButtonEvent, 0 );


   usleep(500000);




   //Get initial Distance
   //======================================
   uart.sendLine(Dist);
   initDist=uart.receiveLineData("013141 31 ",5);
   curDist=initDist;
   //======================================

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
   usleep(500000);

   //Query for Engine Temp
   //======================================
   uart.sendLine(Temp);
   curTemp=uart.receiveLineData("010541 05 ",2);
   //======================================
   usleep(500000);

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

	 //Get the time
	 //======================================
	 time(&rawTime);
	 curTime=localtime(&rawTime);
	 curTime->tm_hour+=timeOffset;
	 //======================================

	 usleep(500000);
	 //if it's been a minute, check fuel level and engine Temp
	 //======================================
	 if(curTime->tm_min!=prevTime->tm_min)
	 {
	    prevTime=localtime(&rawTime);
	    prevTime->tm_hour+=timeOffset;
	    uart.sendLine(Fuel);
	    curFuel=uart.receiveLineData("012F41 2F ",2);
	    usleep(500000);

	    //Query for Engine Temp
	    //======================================
	    uart.sendLine(Temp);
	    curTemp=uart.receiveLineData("010541 05 ",2);
	    //======================================
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
	    sensorPtr0->Send_I2C_Byte(0x00, 0x51);
	    usleep(68E3);
	    leftDist=sensorPtr0->Read_2I2C_Bytes(0x02);
	    sensorPtr1->Send_I2C_Byte(0x00, 0x51);
	    usleep(68E3);
	    rightDist=sensorPtr1->Read_2I2C_Bytes(0x02);
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
	 sensorPtr0->Send_I2C_Byte(0x00, 0x51);
	 usleep(68E3);
	 leftDist=sensorPtr0->Read_2I2C_Bytes(0x02);
	 sensorPtr1->Send_I2C_Byte(0x00, 0x51);
	 usleep(68E3);
	 rightDist=sensorPtr1->Read_2I2C_Bytes(0x02);
	 //======================================

      }
   }
}
