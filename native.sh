#!/bin/sh

g++ -std=c++11 src/path.cc \
    -o path \
    -g \
    src/core/astar.cc src/core/grid.cc src/core/backtrace.cc src/core/smoothenPath.cc && ./path && rm ./path
