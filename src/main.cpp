#include <string>
#include <iostream>
#include <exception>

#include "Exception.h"
#include "SandToy.h"

int main(int argc, char* argv[])
{
  try
  {
    SandToy sandToy;
    sandToy.run();
    return 0;
  }
  catch(std::exception& e)
  {
    std::cerr << "Fatal Error: " << e.what() << std::endl;
    return 1;
  }
}