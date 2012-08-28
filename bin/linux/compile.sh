#!/bin/sh
g++ -shared -Wall -fPIC -g -o tmp/main.tmp -I $1 -L$1 -include hook.h main.cpp 
