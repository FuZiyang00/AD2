#!/bin/bash

set -x # print commands executed

BOOST_ROOT=$1 # example: ~/Desktop/uni/advanced_programming/homeworks/extlib

# execute cmake command
rm -r build
mkdir build
cd build
cmake -DBOOST_ROOT=${BOOST_ROOT} ..
make
cd ..
