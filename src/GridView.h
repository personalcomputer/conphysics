#pragma once

#include "GLFWPixelDisplay.h"
#include "GridModel.h"

class GridView: public GridModelListener
{
  private:
  GLFWPixelDisplay* const pixelDisplay;

  public:
  GridView(GLFWPixelDisplay* const pixelDisplay);
  ~GridView();

  virtual void cellStatusChanged(const glm::ivec2 cellLoc, const Cell& cell);
};