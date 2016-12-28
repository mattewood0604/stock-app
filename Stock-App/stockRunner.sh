#!/bin/bash

DATE=`date +%m_%d_%Y`
mkdir "$DATE"

echo 'g++ *.cpp -lcurl -o ./stocks'
g++ -std=c++11 -Wall -Wextra *.cpp -lcurl -o stocks

echo './stocks'
./stocks
