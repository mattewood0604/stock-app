#!/bin/bash
echo 'g++ -std=c++11 -Wall -Wextra *.cpp -lcurl -o stocks'
g++ -std=c++11 -Wall -Wextra *.cpp -lcurl -o stocks

echo './stocks'
./stocks
