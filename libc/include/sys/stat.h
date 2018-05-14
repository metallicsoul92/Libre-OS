#ifndef LIBC_STAT_H
#define LIBC_STAT_H

#include "cdefs.h"


#ifndef _HAS_STAT
#define _HAS_STAT
struct stat{
  dev_t st_dev;
  ino_t st_ino;
  mode_t st_mode;
  nlink_t st_nlink;
  uid_t st_uid;
  gid_t st_gid;
  dev_t st_rdev;
  off_t st_size;
  struct timespec st_atim;
  struct timespec st_mtim;
  struct timespec st_ctim;
  blksize_t st_blksize;
  blkcnt_t st_blocks;
};
#endif // Has Stat

/* Not standard, used for convenience */
typedef struct stat stat_t;

/* File Types */
#define S_IFMT      0170000
#define S_IFDIR     0040000
#define S_IFCHAR    0020000
#define S_IFBLK     0060000
#define S_IFREG     0100000
#define S_IFIFO     0010000

/* Protection Bits */
#define S_ISUID   04000
#define S_ISGID   02000
#define S_IREAD    0400
#define S_IWRITE   0200
#define S_IEXEC    0100



#endif
