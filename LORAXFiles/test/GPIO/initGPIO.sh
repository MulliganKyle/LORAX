#!/bin/bash
echo 67 > /sys/class/gpio/export
echo both > /sys/class/gpio/gpio67/edge

echo 68 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio68/direction

