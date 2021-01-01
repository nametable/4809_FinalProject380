#!/bin/bash

~/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude \
    -C/home/logan/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf \
    -v -patmega4809 -cxplainedmini_updi -Pusb -b115200 -e -D -U build/4809/src/4809-build/main_4809
