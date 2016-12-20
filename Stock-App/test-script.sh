#!/bin/bash

clear

DATE=`date +%m_%d_%Y`
mkdir "/Users/$USER/Desktop/$DATE"

clear

echo 'g++ *.cpp -lcurl -o ./stocks'
g++ *.cpp -lcurl -o ./stocks

clear

echo './stocks'
./stocks