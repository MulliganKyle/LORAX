#!/bin/bash

sleep 20

if [ ! -f /LORAX/dev_test_mode.txt ]; then
   export DISPLAY=:0;
   sux debian /home/devuser/LORAX/threadMngmt/LORAXexe;
fi
