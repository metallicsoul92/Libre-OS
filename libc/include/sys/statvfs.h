#ifndef LIBC_SYS_STATVFS_H_
#define LIBC_SYS_STATVFS_H_

#ifndef _HAS_FSBLKCNT
#define _HAS_FSBLKCNT
typedef unsigned int fsblkcnt_t;
#endif

#ifndef _HAS_FSFILCNT
#define _HAS_FSFILCNT
typedef unsigned int fsfilcnt_t;
#endif


struct statvfs{
  unsigned long f_bsize;
  unsigned long f_frsize;
  fsblkcnt_t f_blocks;
  fsblkcnt_t f_bfree;
  fsblkcnt_t f_bavail;
  fsfilcnt_t f_files;
  fsfilcnt_t f_favail;
  unsigned long f_fsid;
  unsigned long f_flag;
  unsigned log f_namemax;
};

#define ST_RDONLY (1<<1)
#define ST_NOSUID (1<<5)

int fstatvfs(int,struct statvfs *);
int statvfs(const char *restrict, struct statvfs *restrict);

#endif
