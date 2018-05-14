#ifndef LIBC_UTSNAME_H
#define LIBC_UTSNAME_H

struct utsname{
  char * sysname;
  char * nodename;
  char * release;
  char * version;
  char * machine;
};

typedef struct utsname utsname_t;

int uname(utsname_t *name);

#endif
