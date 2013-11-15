#include "Exception.h"

#include "GLFWPixelDisplay.h"

GLFWPixelDisplay::GLFWPixelDisplay(GLFWwindow* const window, const glm::ivec2 resolution):
  window(window),
  resolution(resolution),
  scale(1),
  pixels(NULL)
{
  glfwMakeContextCurrent(window);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  assert(resolution.x == width);
  assert(resolution.y == height);

  pixels = (GLubyte*)malloc(resolution.x*resolution.y*3);
}

GLFWPixelDisplay::~GLFWPixelDisplay()
{
  free(pixels);
}

void GLFWPixelDisplay::setScale(int scale)
{
  if(resolution.x%scale != 0 || resolution.y%scale != 0)
    throw IncompatibleResolutionException();
  this->scale = scale;
}

glm::ivec2 GLFWPixelDisplay::getScaledResolution() const
{
  return resolution/scale;
}

void GLFWPixelDisplay::refresh()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(resolution.x, resolution.y, GL_RGB, GL_UNSIGNED_BYTE, pixels);

  glfwSwapBuffers(window);
}