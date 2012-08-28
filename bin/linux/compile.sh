#!/bin/sh
g++ -shared -fPIC -g -o tmp/main.tmp -I $1 -L$1 -include hook.h main.cpp 
