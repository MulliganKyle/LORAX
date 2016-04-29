#!/bin/bash
if [ ! -f /home/devuser/LORAX/runExec/inDevMode.txt ]; then
   gksu -u debian 'export DISPLAY=:0';
   #su - debian -c ./home/devuser/LORAX/threadMngmt/OBD2demo;
fi
