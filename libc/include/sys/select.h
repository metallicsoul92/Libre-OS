#ifndef LIBC_SYS_SELECT_H_
#define LIBC_SYS_SELECT_H_

#ifndef _HAS_SUSECONDS
#define _HAS_SUSECONDS
typedef int suseconds_t;
#endif

#ifndef _HAS_TIME
#define _HAS_TIME
typedef int time_t;
#endif

#ifndef _HAS_TIMEVAL
#define _HAS_TIMEVAL
struct timeval{
  time_t tv_sec; //Seconds
  suseconds_t tv_usec; //Microseconds
};
#endif

#ifndef _HAS_TIMESPEC
#define _HAS_TIMESPEC
struct timespec{
  time_t tv_sec;
  long tv_nsec;
};
#endif

#ifndef _HAS_SIGSET
#define _HAS_SIGSET
typedef unsigned int sigset_t;
#endif


#endif
