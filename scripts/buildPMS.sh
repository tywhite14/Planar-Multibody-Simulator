#!/bin/bash

mkdir -p build
cd build
cmake ..
make
cd ..
rm -r build
echo "PMS built"
