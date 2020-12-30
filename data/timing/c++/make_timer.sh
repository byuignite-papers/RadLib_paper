#!/bin/bash

set -x

include="../../installed/include"
lib="../../installed/lib"

g++ -O3 -std=c++11 -I$include -L$lib timer.cc parallel_planes.cc -lradlib -o timer.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_S3_timer.cc parallel_planes.cc -lradlib -o ex_S3_timer.x; 

