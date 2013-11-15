#include "GLFW/glfw3.h"

#include "Exception.h"

#include "SandToy.h"

const glm::ivec2 screenResolution(640, 480);
const std::string appName = "Concentrated Physics";
const int scale = 4;

void glfwErrorCallback(int error, const char* description)
{
  throw GLFWException(description);
}

void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  glfwSetWindowShouldClose(window, GL_TRUE);
}

SandToy::SandToy()
{
  if(!glfwInit())
    throw GraphicsInitException("glfwInit");
  glfwSetErrorCallback(glfwErrorCallback);

  window = glfwCreateWindow(screenResolution.x, screenResolution.y, appName.c_str(), NULL, NULL);
  if(!window)
    throw GraphicsInitException("glfwCreateWindow");
  glfwMakeContextCurrent(window);

  inputTracker = new GLFWInputTracker(window);
  quit = false;

  pixelDisplay = new GLFWPixelDisplay(window, screenResolution);
  pixelDisplay->setScale(scale);

  gridModel = new GridModel(screenResolution);
  gridView = new GridView(pixelDisplay);
  //gridModel.addListener(gridView);
}

SandToy::~SandToy()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void SandToy::run()
{
  while(!quit)
  {
    pixelDisplay->refresh();
    //glfwPollEvents();
  }
}
