#ifndef LIBC_STAT_H
#define LIBC_STAT_H

#include "cdefs.h"


#ifndef _HAS_TIME
#define _HAS_TIME 1
typedef int time_t;
#endif

#ifndef _HAS_BLKCNT
#define _HAS_BLKCNT 1
typedef int blkcnt_t;
#endif

#ifndef _HAS_BLKSIZE
#define _HAS_BLKSIZE 1
typedef int blksize_t;
#endif

#ifndef _HAS_STAT
#define _HAS_STAT 1
struct stat{
  dev_t st_dev;
  ino_t st_ino;
  mode_t st_mode;
  nlink_t st_nlink;
  uid_t st_uid;
  gid_t st_gid;
  dev_t st_rdev;
  off_t st_size;
  time_t st_atim;
  time_t st_mtim;
  time_t st_ctim;
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
#define S_IRWXU   0700 //RWE/ Search by owner
#define S_IRUSR   0400 //Read Permission, owner
#define S_IWUSR   0200 //Write Permission, owner
#define S_IXUSR   0100 //Execute/search permission, owner
#define S_IRWXG   070  //Read, write, execute/search by group
#define S_IRGRP   040  //Read PErmission , group
#define S_IWGRP   020  //Write PEmission, group
#define S_IXGRP   010  //Execute/search permission, group
#define S_IRWXO   07   //Read, Write, execute/search by others
#define S_IROTH   04  //Read permission oothers
#define S_IWOTH   02  //Write perission others
#define S_IXOTH   01  //Execute/search others

int    chmod(const char *, mode_t);
int    fchmod(int, mode_t);
int    fstat(int, struct stat *);
int    lstat(const char *, struct stat *);
int    mkdir(const char *, mode_t);
int    mkfifo(const char *, mode_t);
int    mknod(const char *, mode_t, dev_t);
int    stat(const char *, struct stat *);
mode_t umask(mode_t);


#endif
