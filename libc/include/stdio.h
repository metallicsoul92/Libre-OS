#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H 1

#include "sys/cdefs.h"

#define EOF (-1)

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_IOLOCK
typedef void _IO_lock_t;
#define HAS_IOLOCK 1
#endif


#ifndef HAS_FILE
struct __IO_FILE{
    int _flags;
    //Read
    char* _read_ptr;	/* Current read pointer */
    char* _read_end;	/* End of get area. */
    char* _read_base;	/* Start of putback+get area. */
    //Write
    char* _write_base;	/* Start of put area. */
    char* _write_ptr;	/* Current put pointer. */
    char* _write_end;	/* End of put area. */
   //Buffer
    char* _buf_base;	/* Start of reserve area. */
    char* _buf_end;	/* End of reserve area. */
    /* Base */
    char *_save_base; /* Pointer to start of non-current get area. */
    char *_backup_base;  /* Pointer to first valid character of backup area */
    char *_save_end; /* Pointer to end of non-current get area. */
    struct _IO_marker *_markers;

    struct _IO_FILE *_chain;

    int _fileno;  //file descriptor
  #if 0
    int _blksize;
  #else
    int _flags2;
  #endif
    off_t _old_offset; /* This used to be _offset but it's too small.  */

  #define __HAS_COLUMN /* temporary */
    /* 1+column number of pbase(); 0 is unknown. */
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];

    /*  char* _save_gptr;  char* _save_egptr; */

    _IO_lock_t *_lock;
};


typedef struct  __IO_FILE __FILE;
typedef __FILE FILE;
#define HAS_FILE 1
#endif


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
