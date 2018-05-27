#ifndef LIBC_X_ITOA_H_
#define LIBC_X_ITOA_H_

char* itoa(int val, int base);
char *itoas(int val, char *str, int base);
char* litoa(long val, int base);
char *litoas(long val, char *str, int base);
char* uitoa(unsigned int val, int base);
char *uitoas(unsigned int val, char *str, int base);
int atoi(const char **s);

#endif
