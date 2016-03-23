#!/bin/bash
echo 67 > /sys/class/gpio/export
echo both > /sys/class/gpio/gpio67/edge
