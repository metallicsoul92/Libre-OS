#ifndef LIB_C_DLFCN_H_
#define LIB_C_DLFCN_H_


#define RTLD_LAZY   0x01
#define RTLD_NOW    0x02
#define RTLD_GLOBAL 0x04
#define RTLD_LOCAL  0x08


int dlclose(void *);
char *dlerror(void);
void *dlopen(const char *, int);
void *dlsym(void *restrict , const char * restrict);


#endif
