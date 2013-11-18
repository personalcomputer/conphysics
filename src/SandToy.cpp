#include "GLFW/glfw3.h"

#include "Exception.h"
#include "Util.h"

#include "SandToy.h"

const glm::ivec2 sceneResolution(120, 90);
const int scale = 4;
const glm::ivec2 screenResolution(sceneResolution.x*scale, sceneResolution.y*scale);
const std::string appName = "Concentrated Physics";

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

  gridModel = new GridModel(sceneResolution);
  gridView = new GridView(pixelDisplay);
  gridModel->addListener(gridView);

  /*pixelDisplay->setPixel(glm::ivec2(5,5), glm::vec3(0.0,1.0,0.0));

  std::array<std::array<double, 3>, 3> neighborNewMass = GridModel::massRedistribute(glm::dvec2(0.0,-0.5));
  glm::ivec2 neighborIterator(0, 0);
  for(neighborIterator.x = 0; neighborIterator.x < 3; neighborIterator.x++)
  {
    for(neighborIterator.y = 0; neighborIterator.y < 3; neighborIterator.y++)
    {
      double thisMass = neighborNewMass[neighborIterator.x][neighborIterator.y];
      glm::vec3 color(glm::vec3(1.0,1.0,1.0) * float(thisMass));
      //color = glm::vec3(float(neighborIterator.x)/2.0f, float(neighborIterator.y)/2.0f, 1.0);

      pixelDisplay->setPixel(neighborIterator, color);

      std::cout << "("<<neighborIterator.x<<", "<<neighborIterator.y<<"): " << thisMass << std::endl;
    }
  }*/

  gridModel->injectSpecies(glm::ivec2(50,80), 1, 60.0f);
}

SandToy::~SandToy()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void SandToy::run()
{
  pixelDisplay->refresh();
  while(!quit)
  {
    sleep(0.1);
    gridModel->update(0.1);
    pixelDisplay->refresh();
    //glfwPollEvents();
  }
}
