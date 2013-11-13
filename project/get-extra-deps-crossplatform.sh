#!/bin/bash

#This file is simply to test development environment and deployment schemes and is not what I believe to be a best practice, although hopefully I will learn and get closer to a better method.
#It should probably not be ran blindly, but I expect it to be ran blindly.

echo -e "\e[36;01mGetting additional dependencies.\e[00;00m"
wget https://raw.github.com/personalcomputer/supermake/master/supermake.py

cd ../lib
git clone --depth=1 https://github.com/glfw/glfw.git glfw
cd glfw
cmake . -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=ON -DCMAKE_INSTALL_PREFIX=$(pwd)
make install