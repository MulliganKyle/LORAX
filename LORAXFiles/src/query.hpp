#include "UART.h"
#include "i2c.h"

#include <ctime>
#include <stdint.h>
#include <iostream>
#include <string>
#include <time.h>
#include <glib.h> 
#include <fcntl.h>

#define DEVICE_ADDR0 0x70
#define DEVICE_ADDR1 0x71

   static gboolean onButtonEvent( GIOChannel *channel, GIOCondition condition, gpointer user_data );
   
   void query();
