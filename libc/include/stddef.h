#ifndef STDDEF_H_
#define STDDEF_H_

#ifndef HAVE_NULL
#define NULL ((void*)0)
#define HAVE_NULL 1
#endif

#ifndef HAVE_SIZE_T
typedef long unsigned int size_t;
#define HAVE_SIZE_T 1
#endif

#ifndef HAVE_OFFSETOF
#define offsetof(type,member) ((size_t)&(((type*)0)->member)
#define HAVE_OFFSETOF 1
#endif

#ifndef HAVE_PTRDIFF_T
typedef long int ptrdiff_t;
#define HAVE_PTRDIFF_T 1
#endif

#ifndef HAVE_WCHAR_T
typedef int wchar_t;
#define HAVE_WCHAR_T 1
#endif


#endif//stddef.h
