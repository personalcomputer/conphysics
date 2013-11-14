#pragma once
#include "GLFW/glfw3.h"

#include "GLFWPixelDisplay.h"
#include "GLFWInputTracker.h"
#include "GridModel.h"
#include "GridView.h"

class SandToy
{
  private:
  GLFWwindow* window;
  GLFWPixelDisplay* pixelDisplay;
  GLFWInputTracker* inputTracker;

  bool quit;

  GridModel* gridModel;
  GridView* gridView;

  public:
  SandToy();
  ~SandToy();

  void run();
};