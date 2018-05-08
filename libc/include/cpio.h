#ifndef LIBC_CPIO_H
#define LIBC_CPIO_H

#define MAGIC "070707"

#define C_IRUSR  00000400
#define C_IWUSR  00000200
#define C_IXUSR  00000100
#define C_IRGRP  00000040
#define C_IWGRP  00000020
#define C_IXGRP  00000010
#define C_IROTH  00000004
#define C_IWOTH  00000002
#define C_IXOTH  00000001
#define C_ISUID  00040000
#define C_ISGID  00020000
#define C_ISVTX  00010000
#define C_ISDIR  00400000
#define C_ISFIFO 00100000
#define C_ISREG  01000000
#define C_ISBLK  00600000
#define C_ISCTG  01100000
#define C_ISLNK  01200000
#define C_ISSOCK 01400000

#endif
