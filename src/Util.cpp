#include <sys/time.h>
#include <unistd.h>

#include "Util.h"

double getTime()
{
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec/1000000.0;
}

void sleep(double duration)
{
  usleep(duration*1000000);
}