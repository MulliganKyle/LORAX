#ifndef _BEAGLEI2C_H_
#define _BEAGLEI2C_H_

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#define MAX_BUFFER_SIZE	64

class myI2C {
	int i2cFile;
public:
	myI2C();
	~myI2C();
	
	// Public Variables
	unsigned char I2C_WR_Buf[MAX_BUFFER_SIZE];			// Contains data you want to send
	unsigned char I2C_RD_Buf[MAX_BUFFER_SIZE];			// Contains data which was read
	
	// Initialize Functions
	void i2cOpen();										// Opens i2cbus 3, done at the beginning
	void i2cClose();									// Closes i2cbus 3, done at the ending
	void i2cSetAddress(int address);					// Changes device address
	
	// Sends a single byte <Data> to <DEVICE_ADDR> on the register <Reg_ADDR>
	void Send_I2C_Byte(unsigned char Reg_ADDR, unsigned char Data);	

	// Reads and returns a single byte from <DEVICE_ADDR> on the register <Reg_ADDR>
	unsigned char Read_I2C_Byte(unsigned char Reg_ADDR);
	
	// Reads multipes byte from <DEVICE_ADDR> starting from the register address <Reg_ADDR>.
	// Read the output from i2cptr->I2C_RD_Buf
	unsigned char Read_Multi_Byte(unsigned char Reg_ADDR, size_t n);
 
  int Read_All_I2C_Byte(unsigned char Reg_ADDR);
};
#endif /* BEAGLEI2C.H */
