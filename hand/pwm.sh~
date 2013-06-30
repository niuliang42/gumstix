#!/bin/bash
insmod pwm.ko timers=8 servo=1 servo_min=5000 servo_max=25000

echo 5000 > /dev/pwm8
echo 5000
sleep 3s

echo 10000 > /dev/pwm8
echo 10000
sleep 3s

echo 15000 > /dev/pwm8
echo 15000
sleep 3s

echo 20000 > /dev/pwm8
echo 20000
sleep 3s


echo 25000 > /dev/pwm8
echo 25000
sleep 3s

rmmod pwm
