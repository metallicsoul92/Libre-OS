#ifndef LIBC_TIME_H
#define LIBC_TIME_H

#include "sys/cdefs.h"

typedef long int time_t;

struct tm{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_isdst;
};


#ifndef _HAS_TIMESPEC
#define _HAS_TIMESPEC
struct timespec{
  time_t tv_sec;
  long tv_nsec;
};
#endif

struct itimerspec{
  struct timespec it_interval;
  struct timespec it_value;
};



#endif
