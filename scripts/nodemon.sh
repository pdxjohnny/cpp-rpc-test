#!/bin/bash

ln -s makefile makefile.make
ln -s rpc/makefile rpc/makefile.make
nodemon -e c,cpp,h,make --exec 'clear; cd rpc; make clean && make; cd ..; make clean && make && ./bin/rpc-test; exit 0'

