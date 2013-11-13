#!/bin/bash


#If you have any interest in Supermake, this is a poor demo of it. The experimental environment I set up here is too complicated for the situations Supermake is intended for. As the creator I happen to know how to work with it to handle any sophisticated situation, but it's really not advised.

if $1 == 'debug'
  python supermake.py --src=../src --binary=../conphysics --makefile-only --warn --prefix=debug --debug --custom="-I../lib/glfw/include -L../lib/glfw/lib -lglfw3" &&
  cat makefile-append >> makefile &&
  make &&
  make test
else
  python supermake.py --src=../src --binary=../conphysics --no-run --optimize --custom="-I../lib/glfw/include -L../lib/glfw/lib -lglfw3"
fi