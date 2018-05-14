#ifndef LIBC_SYS_TIME_H_
#define LIBC_SYS_TIME_H_

#ifndef _HAS_SUSECONDS
#define _HAS_SUSECONDS
typedef int suseconds_t;
#endif

#ifndef _HAS_TIME
#define _HAS_TIME
typedef int time_t;
#endif


#define ITIMER_REAL
#define ITIMER_VIRTUAL
#define ITIMER_PROF

struct timeval{
  time_t tv_sec; //Seconds
  suseconds_t tv_usec; //Microseconds
};

struct itimerval{
  struct timeval it_interval; //Timer interval
  struct timeval it_value; //Current Value
};


int getitimer(int,struct itimerval *);
int gettimeofday(struct timeval *restrict,void *restrict);
int setitimer(int,const struct itimerval *restrict, struct itimerval *restrict);
int select(int, fd_set *restrict,fd_set *restrict, fd_set *restrict,
          struct timeval *restrict);
int utimes(const char *,const struct timeval[2]);

#endif
