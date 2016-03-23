#!/bin/bash

modprobe pwm_test
echo am33xx_pwm > /sys/devices/bone_capemgr.9/slots
echo bone_pwm_P8_19 > /sys/devices/bone_capemgr.9/slots
echo 1000000 > /sys/devices/ocp.3/pwm_test_P8_19.16/period
echo 500000 > /sys/devices/ocp.3/pwm_test_P8_19.16/duty
echo 0 > /sys/devices/ocp.3/pwm_test_P8_19.16/run

