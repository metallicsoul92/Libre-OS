#ifndef LIBC_SYS_TIMES_H_
#define LIBC_SYS_TIMES_H_

#ifndef _HAS_CLOCK
#define _HAS_CLOCK
typedef int clock_t;
#endif

struct tms{
  clock_t tms_utime; //User CPU time.
  clock_t tms_stime; //System CPU time.
  clock_t tms_cutime;  //User CPU time of terminated child process.
  clock_t tms_cstime;  //System CPU time of terminated child process.
};

clock_t times(struct tms *);

#endif
