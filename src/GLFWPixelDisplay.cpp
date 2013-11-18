#include <cstring>

#include "Exception.h"

#include "GLFWPixelDisplay.h"

GLFWPixelDisplay::GLFWPixelDisplay(GLFWwindow* const window, const glm::ivec2 resolution):
  window(window),
  resolution(resolution),
  scale(1),
  pixels(new GLubyte[resolution.x*resolution.y*3])
{
  glfwMakeContextCurrent(window);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  assert(resolution.x == width);
  assert(resolution.y == height);

  memset(pixels.get(), 0, resolution.x*resolution.y*3);
}

void GLFWPixelDisplay::setScale(int scale)
{
  if(resolution.x%scale != 0 || resolution.y%scale != 0)
    throw IncompatibleResolutionException();
  this->scale = scale;
}

glm::ivec2 GLFWPixelDisplay::getResolution() const
{
  return resolution/scale;
}

void GLFWPixelDisplay::refresh()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(resolution.x, resolution.y, GL_RGB, GL_UNSIGNED_BYTE, pixels.get());

  glfwSwapBuffers(window);
}