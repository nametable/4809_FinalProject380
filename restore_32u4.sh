#!/bin/bash

# https://forum.arduino.cc/index.php?topic=584239.0
# DFU mode ->  While PE2 test point is connected to GND, connect RST pin test pin to GND and then release

dfu-programmer atmega32u4 erase
sleep 2
dfu-programmer atmega32u4 flash 32u4/medbgupdi.hex
sleep 2
dfu-programmer atmega32u4 reset

