#!/bin/bash
g++ -c -I. -Wall *.cpp && g++ -o rot -Wall -Wl,--enable-auto-import *.o
