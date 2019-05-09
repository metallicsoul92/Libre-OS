#ifndef LIBC_ERRNO_H_
#define LIBC_ERRNO_H_


#ifdef __is_libk
  #define _SIGN -
  #define OK 0
#else
  #define _SIGN
#endif



//This is based off Linux's error numbers

#define EPERM       (_SIGN 1)  /* Operation not permitted */
#define ENOENT       (_SIGN 2)  /* No such file or directory */
#define ESRCH        (_SIGN 3)  /* No such process */
#define EINTR       (_SIGN 4)  /* Interrupted system call */
#define EIO     (_SIGN 5)  /* I/O error */
#define ENXIO       (_SIGN 6)  /* No such device or address */
#define E2BIG       (_SIGN 7)  /* Argument list too long */
#define ENOEXEC     (_SIGN 8)  /* Exec format error */
#define EBADF      (_SIGN  9)  /* Bad file number */
#define ECHILD     (_SIGN 10)  /* No child processes */
#define EAGAIN     (_SIGN 11)  /* Try again */
#define ENOMEM     (_SIGN 12)  /* Out of memory */
#define EACCES      (_SIGN 13)  /* Permission denied */
#define EFAULT     (_SIGN 14)  /* Bad address */
#define ENOTBLK   (_SIGN  15)  /* Block device required */
#define EBUSY      (_SIGN 16)  /* Device or resource busy */
#define EEXIST     (_SIGN 17)  /* File exists */
#define EXDEV      (_SIGN 18)  /* Cross-device link */
#define ENODEV     (_SIGN 19)  /* No such device */
#define ENOTDIR    (_SIGN 20)  /* Not a directory */
#define EISDIR     (_SIGN 21)  /* Is a directory */
#define EINVAL     (_SIGN 22)  /* Invalid argument */
#define ENFILE     (_SIGN 23)  /* File table overflow */
#define EMFILE     (_SIGN 24)  /* Too many open files */
#define ENOTTY     (_SIGN 25)  /* Not a typewriter */
#define ETXTBSY    (_SIGN 26)  /* Text file busy */
#define EFBIG      (_SIGN 27)  /* File too large */
#define ENOSPC     (_SIGN 28)  /* No space left on device */
#define ESPIPE     (_SIGN 29)  /* Illegal seek */
#define EROFS      (_SIGN 30)  /* Read-only file system */
#define EMLINK     (_SIGN 31)  /* Too many links */
#define EPIPE      (_SIGN 32)  /* Broken pipe */
#define EDOM       (_SIGN 33)  /* Math argument out of domain of func */
#define ERANGE     (_SIGN 34)  /* Math result not representable */


#endif //errno.h
