#include "i2c.h"
#include <iostream>
#include <stdio.h>

// Define device address
// It is a better idea to include all the addresses in a header file
// #define DEVICE_ADDR 0xE0
#define DEVICE_ADDR0 0x70
#define DEVICE_ADDR1 0x71

// Define register address
#define CTRL_REG1 0x00
#define STATUS_REG 0x02

using namespace std;

int main(){
   // Instantiate the I2c Object
   myI2C *sensorptr0 = new myI2C();
   myI2C *sensorptr1 = new myI2C();
   

   unsigned char value;
   int value1, value2;
   int finalValue;


   sensorptr0->i2cSetAddress(DEVICE_ADDR0);
   sensorptr1->i2cSetAddress(DEVICE_ADDR1);
   usleep(500E3);



#if 1

   for (int i = 0 ; i < 1 ; i++) {

      // Trigger start of ranging
      //Sensor0
      sensorptr0->Send_I2C_Byte(CTRL_REG1, 0x51); 

      usleep(68E3); // 65 mS is nominal with Range Register = 0xFF

      cout<< "I2C 0: " << endl;
      value1 = sensorptr0->Read_All_I2C_Byte(0x0);
      

      //Sensor1
      sensorptr1->Send_I2C_Byte(CTRL_REG1, 0x51);

      usleep(68E3);


      cout<< "I2C 1: " << endl;
      value1 = sensorptr1->Read_All_I2C_Byte(0x0);
      
      usleep(500E3);
   }

#endif

   return 0;
}
