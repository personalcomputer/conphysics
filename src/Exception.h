#pragma once
#include <string>
#include <exception>

class Exception : public std::exception
{
  public:
  std::string title;
  std::string description;

  Exception(const std::string& title, const std::string& description="");
  inline virtual ~Exception() throw() {}
  virtual std::string report() const;
  virtual const char* what() const throw();
};

class FatalException : public Exception
{
  public:
  FatalException(const std::string& title, const std::string& description="") : Exception(title, description) {}
};

class GraphicsInitException : public FatalException
{
  public:
  inline GraphicsInitException(const std::string& description=""): FatalException("GraphicsInitException", description) {}
};

class GLFWException : public FatalException
{
  public:
  inline GLFWException(const std::string& description=""): FatalException("GLFWException", description) {}
};

class IncompatibleResolutionException : public Exception
{
  public:
  inline IncompatibleResolutionException(const std::string& description=""): Exception("IncompatibleResolutionException", description) {}
};


