#!/bin/bash


#If you have any interest in Supermake, this is a poor demo of it. The experimental environment I set up here is too complicated for the situations Supermake is intended for. As the creator I happen to know how to work with it to handle any sophisticated situation, but it's really not advised.

if [ $1 == 'debug' ]
then
  python supermake.py --src=../src --binary=../conphysics --makefile-only --warn --prefix=debug --debug --custom="-I../lib/glfw/include -I../lib/glm -L../lib/glfw/lib -lglfw3 -lGL -lXrandr -lXi -lX11"
  cat makefile-append >> debugmakefile
  make -f debugmakefile
  make -f debugmakefile test
else
  python supermake.py --src=../src --binary=../conphysics --no-run --optimize --custom="-I../lib/glfw/include -I../lib/glm -L../lib/glfw/lib -lglfw3 -lGL -lXrandr -lXi -lX11"
fi