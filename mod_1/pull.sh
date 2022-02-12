#!/usr/bin/env bash

make clean
git pull
make
sudo dmesg --clear
sudo insmod main.ko
sudo rmmod main
clear
dmesg
