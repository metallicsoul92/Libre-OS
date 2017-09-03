#ifndef _STDIO_H
#define _STDIO_H 1

#include "sys/cdefs.h"

#define EOF (-1)

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct __IO_FILE;
typedef struct  __IO_FILE __FILE;


extern struct __IO_FILE * stdin;
extern struct __IO_FILE * stdout;
extern struct __IO_FILE * stderr;

/* C89/C99 say these are macros.  */
#define stdin stdin
#define stdout stdout
#define stderr stderr

int vsprintf(char *buf, const char *fmt,...);

int printf(const char* __restrict, ...);
int sprintf (char *string, const char *form,...);


int putchar(int);

int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif
