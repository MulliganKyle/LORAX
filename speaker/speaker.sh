#!/bin/bash

echo 1000000 > /sys/devices/ocp.3/pwm_test_P8_19.16/period
echo 500000 > /sys/devices/ocp.3/pwm_test_P8_19.16/duty

echo 1 > /sys/devices/ocp.3/pwm_test_P8_19.16/run
sleep 1
echo 0 > /sys/devices/ocp.3/pwm_test_P8_19.16/run
sleep 1


echo 1 > /sys/devices/ocp.3/pwm_test_P8_19.16/run
sleep 1
echo 0 > /sys/devices/ocp.3/pwm_test_P8_19.16/run
sleep 1

echo 1 > /sys/devices/ocp.3/pwm_test_P8_19.16/run
sleep 1
echo 0 > /sys/devices/ocp.3/pwm_test_P8_19.16/run
sleep 1

