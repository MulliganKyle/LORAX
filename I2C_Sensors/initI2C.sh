#!/bin/bash
 
echo BB-I2C1 > /sys/devices/bone_capemgr.9/slots

echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-2/new_device
hwclock -s -f /dev/rtc1
hwclock -w
