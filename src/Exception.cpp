#include "Exception.h"

Exception::Exception(const std::string& title, const std::string& description)
{
  this->title = title;
  this->description = description;
}

std::string Exception::report() const
{
  return title + ": " + description;
}

const char* Exception::what() const throw()
{
  return report().c_str();
}

std::string FatalException::report() const
{
  return title + " (FATAL): " + description;
}