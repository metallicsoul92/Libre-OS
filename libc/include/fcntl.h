#ifndef LIBC_FCNTL_H
#define LIBC_FCNTL_H

#define F_DUPFD        0  // Duplicatefile descriptor.
#define F_GETFD        1  // Getfile descriptor flags.
#define F_SETFD        2  // Setfile descriptor flags.
#define F_GETFL        3  // Getfile status flags and file access modes.
#define F_SETFL        4  // Setfile status flags.
#define F_GETLK        5  // Getrecordlocking information.
#define F_SETLK        6  // Setrecordlocking information.
#define F_SETLKW       7  // Setrecordlocking information; wait if blocked.
#define F_GETOWN       8  // Getprocess or process group ID to receive SIGURG signals.
#define F_SETOWN       9  // Setprocess or process group ID to receive SIGURG signals

#define FD_CLOEXEC 1

/* For posix fcntl() and `l_type' field of a `struct flock' for lockf().  */
#define F_RDLCK      0        /* Read lock.  */
#define F_WRLCK      1        /* Write lock.  */
#define F_UNLCK      2        /* Remove lock.  */

#define O_CREAT     001    //  Create file if it does not exist.
#define O_EXCL      002    //  Exclusiveuse flag.
#define O_NOCTTY    010    //  Don ot assign controlling terminal.
#define O_TRUNC     011    //  Truncate flag.
#define O_APPEND    020    //  Set append mode.
#define O_DSYNC     021    //  Write according to synchronized I/O data
                           //  integrity completion.
#define O_NONBLOCK  022    // Non-blocking mode.
#define O_RSYNC     100    // Synchronized read I/O operations.
#define O_SYNC      101    // Write according to synchronized I/O file
                           // integrity completion.

#define O_ACCMODE           0003

#define O_EXEC        100   //   Open for execute only (non-directory files).
                            //   Use of this flag on directoriesis currently
                            //   unspecified.
#define O_RDONLY      001   //   Open for reading only.
#define O_RDWR        011   //   Openfor reading and writing.
#define O_WRONLY      010   //   Open for writing only.

#ifndef HAS_MODE_T
typedef unsigned short mode_t;	   /* file type and permissions bits */
#define HAS_MODE_T 1
#endif

#define AT_FDCWD                -100
#define AT_EACCESS             0x200
#define AT_SYMLINK_NOFOLLOW    0x100
#define AT_SYMLINK_FOLLOW      0x400

#define O_DIRECTORY        0200000
#define  O_NOFOLLOW        0400000

#  define __POSIX_FADV_DONTNEED   4
#  define __POSIX_FADV_NOREUSE    5

# define POSIX_FADV_NORMAL        0 /* No further special treatment.  */
# define POSIX_FADV_RANDOM        1 /* Expect random page references.  */
# define POSIX_FADV_SEQUENTIAL    2 /* Expect sequential page references.  */
# define POSIX_FADV_WILLNEED      3 /* Will need these pages.  */
# define POSIX_FADV_DONTNEED      __POSIX_FADV_DONTNEED /* Don't need these pages.  */
# define POSIX_FADV_NOREUSE       __POSIX_FADV_NOREUSE /* Data will be accessed once.  */

#ifndef HASFLOCK
struct _flock{
  short  l_type;   //Type of lock; F_RDLCK, F_WRLCK, F_UNLCK.
  short  l_whence; //Flag for starting offset.
  off_t  l_start;  //Relative offset in bytes.
  off_t  l_len;   //Size; if 0 then until EOF.
  pid_t  l_pid;   //Process ID of the process holding the lock; returned with F_GETLK.
};
typedef struct _flock flock;
#define HASFLOCK 1
#endif

#ifndef _HAS_MODE
#define _HAS_MODE 1
typedef int mode_t;
#endif

#ifndef _HAS_OFF
#define _HAS_OFF 1
typedef int off_t;
#endif

#ifndef _HAS_PID
#define _HAS_PID 1
typedef int pid_t;
#endif

int  creat(const char *, mode_t);
int  fcntl(int,int, ...);
int  open(const char *, int, ...);
int  openat(int,const char *, int, ...);
int  posix_fadvise(int,off_t, off_t, int);
int  posix_fallocate(int,off_t, off_t);

#endif
