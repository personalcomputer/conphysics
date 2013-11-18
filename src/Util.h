#pragma once
#include <glm/glm.hpp>

template<typename T>
T linearInterp(double f, const T& a, const T& b)
{
  return f*a + (1-f)*b;
}

double getTime(); //in seconds
void sleep(double duration); //in seconds