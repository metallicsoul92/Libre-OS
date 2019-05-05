#ifndef LIBC_STDDEF_H_
#define LIBC_STDDEF_H_

#ifndef HAS_NULL
#define NULL ((void*)0)
#define HAS_NULL 1
#endif

#ifndef HAS_SIZE_T
typedef long unsigned int size_t;
#define HAS_SIZE_T 1
#endif

#ifndef HAS_OFFSETOF
#define offsetof(type,member) ((size_t)&(((type*)0)->member)
#define HAS_OFFSETOF 1
#endif

#ifndef HAS_PTRDIFF_T
typedef long int ptrdiff_t;
#define HAS_PTRDIFF_T 1
#endif

#ifndef HAS_WCHAR_T
typedef int wchar_t;
#define HAS_WCHAR_T 1
#endif


#endif//stddef.h
