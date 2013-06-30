#!/bin/bash
insmod pwm.ko timers=8 servo=1 servo_min=5000 servo_max=25000
echo $1 > /dev/pwm8
rmmod pwm
