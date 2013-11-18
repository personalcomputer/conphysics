#pragma once
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

class GLFWPixelDisplay
{
  private:
  GLFWwindow* const window;
  glm::ivec2 resolution;
  int scale;
  std::unique_ptr<GLubyte[]> pixels;

  inline void setPixelRaw(glm::ivec2 loc, glm::vec3 color)
  {
    pixels[(loc.y*(resolution.x*3))+(loc.x*3)  ] = (unsigned char) ((color.r)*255);
    pixels[(loc.y*(resolution.x*3))+(loc.x*3)+1] = (unsigned char) ((color.g)*255);
    pixels[(loc.y*(resolution.x*3))+(loc.x*3)+2] = (unsigned char) ((color.b)*255);
  }

  public:
  GLFWPixelDisplay(GLFWwindow* const window, const glm::ivec2 resolution);

  void setScale(int scale);

  inline void setPixel(glm::ivec2 loc, glm::vec3 color)
  {
    if(scale == 1)
      setPixelRaw(loc, color);
    else
    {
      for(int pixelIndex = 0; pixelIndex < scale*scale; pixelIndex++)
      {
        glm::ivec2 rawLoc = loc*scale;
        rawLoc.x += pixelIndex%scale;
        rawLoc.y += pixelIndex/scale;
        setPixelRaw(rawLoc, color);
      }
    }
  }

  glm::ivec2 getResolution() const;

  void refresh();
};