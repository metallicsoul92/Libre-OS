#ifndef LIBC_STAT_H
#define LIBC_STAT_H

#include "cdefs.h"


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
int    fchmodat(int, const char *, mode_t, int);
int    fstat(int, struct stat *);
int    fstatat(int, const char *restrict, struct stat *restrict, int);
int    futimens(int, const struct timespec [2]);
int    lstat(const char *restrict, struct stat *restrict);
int    mkdir(const char *, mode_t);
int    mkdirat(int, const char *, mode_t);
int    mkfifo(const char *, mode_t);
int    mkfifoat(int, const char *, mode_t);
int    mknod(const char *, mode_t, dev_t);
int    mknodat(int, const char *, mode_t, dev_t);
int    stat(const char *restrict, struct stat *restrict);
mode_t umask(mode_t);
int    utimensat(int, const char *, const struct timespec [2], int);


#endif
