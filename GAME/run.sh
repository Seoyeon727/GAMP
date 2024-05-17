#!/bin/bash

# a) Install dependencies
apt-get update
apt-get install -y cmake g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

# b) Run all necessary parts of the codebase
mkdir build
cd build
cmake ..
make
./GaDaeroJourney
