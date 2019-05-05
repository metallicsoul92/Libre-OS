#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H 1

#include "sys/cdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

char *itoa(int val, int base);
char *itoas(int val, char *str, int base);
char *uitoa(unsigned int val, int base);
char *uitoas(unsigned int val, char *str, int base);
char *litoa(long val, int base);
char *litoas(long val, char *str, int base);


#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))



#ifdef __cplusplus
}
#endif

#endif
