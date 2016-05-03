#!/bin/bash

if [ ! -f /LORAX/installed.txt ]; then

   > /LORAX/installed.txt


   ##############################################
   #init files
   #############################################
   cp init_speaker.sh /etc/init.d/init_speaker.sh
   update-rc.d /etc/init.d/init_speaker.sh defaults

   cp initGPIO.sh /etc/init.d/initGPIO.sh
   update-rc.d /etc/init.d/initGPIO.sh defaults

   cp initI2C.sh /etc/init.d/initI2C.sh
   update-rc.d /etc/init.d/initI2C.sh defaults

   cp initOBD2.sh /etc/init.d/initOBD2.sh
   update-rc.d /etc/init.d/init_speaker.sh defaults

   cp initSD.sh /etc/init.d/initSD.sh
   update-rc.d /etc/init.d/initSD.sh defaults


   cp runExec.sh /etc/init.d/runExec.sh
   update-rc.d /etc/init.d/initSD.sh defaults

   ###############################
   #format and mount the SD card
   ###############################


   mkntfs /dev/mmcblk0

   mount -t ntfs -v /dev/mmcblk0 /mnt/SD
   mkdir /mnt/SD/logs

   #################################
   #install apps
   ###################################


   apt-get install sux



   ################################
   #openCV
   ################################


   apt-get install build-essential cmake git pkg-config

   mkdir /mnt/SD/local

   cd /mnt/SD

   git clone https://github.com/Itseez/opencv.git

   cd opencv

   mkdir build

   cd build

   cmake -D INSTALL_C_EXAMPLES=OFF -D CMAKE_INSTALL_PREFIX=/mnt/SD/local ..

   make
   make install




fi
