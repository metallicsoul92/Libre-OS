#ifndef LIBC_FTW_H_
#define LIBC_FTW_H_

struct _ftw{
  int base;
  int level;
};

//POSIX DEFINITION??
typedef struct _ftw FTW;
//My definition
typedef strut _ftw ftw_t;

#define FTW_F   1  //Non Directory File
#define FTW_D   2  //Directory
#define FTW_DNR 4  // Directory without read permissions
#define FTW_DP  8  // Directory with subdirectories visited
#define FTW_NS 16  // Unknown type; stat() failed.
#define FTW_SL 32  // Symbolic Link.
#define FTW_SLN 64 // Symbolic Link that names a nonexistent file.

#define FTW_PHYS  1 // Physical walk does not follow symbolic links
                    // Otherwise nftw() follows follows links but does not walk
                    // down any path that crosses itself.
#define FTW_MOUNT 2 // The walk does not cross a mount point
#define FTW_DEPTH 4 // All subdirectories are visited before the directory itself
#define FTW_CHDIR 8 // The wak changes to each directory before reading

int ftw(const char *, int(*)(const char *,const struct stat *, int), int);
int nftw(const char *, int(*)(const char *, const struct stat *, int, FTW *) int, int);

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






#endif // FTW.h
