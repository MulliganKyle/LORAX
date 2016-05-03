#!/bin/bash
if [ ! -f /home/devuser/LORAX/runExec/inDevMode.txt ]; then
   export DISPLAY=:0;
   sux debian /home/devuser/LORAX/threadMngmt/OBD2demo;
fi
