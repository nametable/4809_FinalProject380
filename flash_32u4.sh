#!/bin/bash

# https://forum.arduino.cc/index.php?topic=584239.0
# DFU mode ->  While PE2 test point is connected to GND, connect RST pin test pin to GND and then release

dfu-programmer atmega32u4 erase
sleep 2
/home/logan/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-objcopy -O ihex build/32u4/src/32u4-build/main_32u4 build/32u4/src/32u4-build/main_32u4.hex
dfu-programmer atmega32u4 flash build/32u4/src/32u4-build/main_32u4.hex
sleep 2
dfu-programmer atmega32u4 reset

# avrdude -p atmega32u4 -c usbasp -U flash:w:keyboard.hex