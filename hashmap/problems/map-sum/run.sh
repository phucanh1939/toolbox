#!/bin/sh

set -e

mkdir -p bin
mkdir -p benchmark

g++ -std=c++17 -O2 src/MapSum.cpp src/main.cpp -o bin/a.out

./bin/a.out benchmark/benchmark.txt