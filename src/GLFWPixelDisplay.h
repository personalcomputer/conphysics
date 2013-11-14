#pragma once
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

class GLFWPixelDisplay
{
  private:

  public:
  GLFWPixelDisplay(GLFWwindow* const window, const glm::ivec2 resolution);
  ~GLFWPixelDisplay();
};