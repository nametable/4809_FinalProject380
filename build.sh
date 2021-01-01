#!/bin/bash
cd ./build
make -j12 #VERBOSE=1
cd ./32u4/src/32u4-build
make -j12
cd ../../../4809/src/4809-build
make -j12