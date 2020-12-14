#!/bin/bash

./compile.sh $1

echo one.temp
./run.out one.temp
echo -----------------------------------------------------
echo two.temp
./run.out two.temp
echo -----------------------------------------------------
echo input test
./run.out
