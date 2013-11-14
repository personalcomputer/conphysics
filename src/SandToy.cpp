#include "GLFW/glfw3.h"

#include "Exception.h"

#include "SandToy.h"

const glm::ivec2 screenResolution(640, 480);
const std::string appName = "Concentrated Physics";

SandToy::SandToy()
{
  if(!glfwInit())
    throw GraphicsInitException("glfwInit");

  window = glfwCreateWindow(screenResolution.x, screenResolution.y, appName.c_str(), NULL, NULL);
  if(!window)
    throw GraphicsInitException("glfwCreateWindow");
  glfwMakeContextCurrent(window);

  pixelDisplay = new GLFWPixelDisplay(window, screenResolution);
  inputTracker = new GLFWInputTracker(window);
  quit = false;
  gridModel = new GridModel(screenResolution);
  gridView = new GridView(pixelDisplay);

  //gridModel.addListener(gridView);
}

SandToy::~SandToy()
{
  glfwTerminate();
}


void SandToy::run()
{
  while(!quit)
  {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
