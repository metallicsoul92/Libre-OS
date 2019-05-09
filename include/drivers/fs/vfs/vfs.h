#ifndef DRIVER_VFS_FS_H
#define DRIVER_VFS_FS_H

#include "../../../../libc/include/stdlib.h"
#include "../../../../libc/include/sys/cdefs.h"
#include "../../../../libc/include/sys/stat.h"
#include "../../../../libc/include/stddef.h"
#include "../../../kmem.h"



struct vfs_dirent{
    size_t _ino;
    char _name[256];
};
typedef struct vfs_dirent vfs_dirent_t;

struct _mnt{
  const char *dev;
  const char *path;
  const char *type;
  const char *options;
};
typedef struct _mnt vfs_mount_t;


struct vfs_uio {
    char     *root; /* Root Directory */
    char     *cwd;  /* Current Working Directory */
    uid_t    uid;
    gid_t    gid;
    mode_t   mask;
    uint32_t flags;
};
typedef struct vfs_uio uio_t;

struct vfs_file{
    struct _vfs_inode *inode;

    off_t offset;
    int flags;
};

typedef struct vfs_file vfs_file_t;

struct _vfs_file_ops{
  int     (*open)      (vfs_file_t *file);
  ssize_t (*read)      (vfs_file_t *file, void *buf, size_t size);
  ssize_t (*write)     (vfs_file_t *file, void *buf, size_t size);
  ssize_t (*readdir)   (vfs_file_t *file, vfs_dirent_t *dirent);
  off_t   (*lseek)     (vfs_file_t *file, off_t offset, int whence);
  int     (*close)     (vfs_file_t *file);
  int     (*ioctl)     (vfs_file_t *file, int request, void *argp);
  int     (*trunc)     (vfs_file_t *file, off_t len);
  int     (*can_read)  (vfs_file_t *file, size_t size);
  int     (*can_write) (vfs_file_t *file, size_t size);
  int     (*eof)       (vfs_file_t *);
};
typedef struct _vfs_file_ops vfs_fileOps_t;

struct _vfs_inode {
  ino_t ino;
  size_t size;
  dev_t device;
  dev_t rdevice;
  mode_t mode;
  uid_t uid;
  gid_t gid;
  nlink_t nlink;
  time_t atime;
  time_t mtime;
  time_t ctime;

  struct fs * fs;
  void        *fsPrivData;

   /* Number of processes referencing this node */
   ssize_t     ref;

   struct queue     *read_queue;
   struct queue     *write_queue;
};
typedef struct _vfs_inode vfs_inode_t;

struct _vfs_vnode;
struct _vfs_inode_ops{
  ssize_t (*read)    (vfs_inode_t *inode, off_t offset, size_t size, void *buf);
  ssize_t (*write)   (vfs_inode_t *inode, off_t offset, size_t size, void *buf);
  int     (*ioctl)   (vfs_inode_t *inode, int request, void *argp);
  ssize_t (*readdir) (vfs_inode_t *inode, off_t offset, vfs_dirent_t *dirent);
  int     (*close)   (vfs_inode_t *inode);
  int     (*trunc)   (vfs_inode_t *inode, off_t len);

  int     (*vmknod)  (struct _vfs_vnode *dir, const char *fn, uint32_t mode, dev_t dev, uio_t *uio, vfs_inode_t **ref);
  int     (*vunlink) (struct _vfs_vnode *dir, const char *fn, uio_t *uio);
  int     (*vfind)   (struct _vfs_vnode *dir, const char *name, struct _vfs_vnode *child);
  int     (*vget)    (struct _vfs_vnode *vnode, vfs_inode_t **inode);
  int     (*map)     (struct vm_entry *vm_entry);
};
typedef struct _vfs_inode_ops vfs_inodeOps_t;

struct _vfs_vnode{
  ino_t ino;
  mode_t mode;
  uid_t  uid;
  gid_t  gid;

  vfs_inode_t *super;
};

typedef struct _vfs_vnode vfs_vnode_t;

struct fs {
  char *name;
  int (*init)();
  int (*load)(vfs_inode_t *dev, vfs_inode_t **super);
  int (*mount)(const char *dir, int flags, void *data);

  vfs_inodeOps_t iopts;
  vfs_fileOps_t fops;

  int nodev;
};
typedef struct fs fs_t;

struct list_fs{
  const char *name;
  fs_t * fs;
  struct list_fs *next;
};
typedef struct list_fs list_fs_t;

struct _vfs_path{
  vfs_inode_t *mnt;
  char **tokens;
};
typedef struct _vfs_path vfs_path_t;

struct _vfs_node {
    const char * name;
    struct _vfs_node * children;
    struct _vfs_node * parent;
    vfs_inode_t * iref;
};

typedef struct _vfs_node vfs_node_t;

extern list_fs_t *registered_fs;
extern vfs_inode_t *vfs_root;

/*Functions*/
void vfsInit(void);
int vfsInstall(fs_t * fs);
void vfsMountRoot(vfs_inode_t *inode);
int vfsBind(const char * path, vfs_inode_t *target);
int vfsMount(const char *type, const char *dir, int flags, void *data,uio_t *uio);

//vnode Data
int vfsVmknod(vfs_vnode_t * dir, const char *fn, uint32_t mode, dev_t dev,
              uio_t *uio, vfs_inode_t **ref);
int vfsVmcreat(vfs_vnode_t * dir, const char *fn, uio_t *uio, vfs_inode_t **ref);
int vfsVmkdir(vfs_vnode_t *dir, const char *dname, uio_t *uio, vfs_inode_t **ref);
int vfsVunlink(vfs_vnode_t *dir, const char *fn, uio_t * uio);
int vfsVfind(vfs_vnode_t * vnode, const char * name , vfs_vnode_t * child);
int vfsVget(vfs_vnode_t *vnode, vfs_inode_t **inode);
int vfsMap(vm_entry_t * entry); //TODO: Setup VM_ENTRY In memory managers
ssize_t vfsRead(vfs_inode_t *inode,off_t offset, size_t size, void *buffer);
ssize_t vfsWrite(vfs_inode_t *inode,off_t offset, size_t size, void *buffer);
ssize_t vfsReaddir(vfs_inode_t *inode, off_t offset, vfs_dirent_t *dirent);
int vfsIoctl(vfs_inode_t *inode, unsigned long req, void *argp);
int vfsClose(vfs_inode_t *inode);
int vfsTrunc(vfs_inode_t *inode, off_t len);
int vfsFileOpen(vfs_file_t *file);
ssize_t vfsFileRead(vfs_file_t *file, void *buffer, size_t size);
ssize_t vfsFileWrite(vfs_file_t *file, void *buffer, size_t size);
ssize_t vfsFileReaddir(vfs_file_t *file,vfs_dirent_t *dirent);
off_t vfsFileLseek(vfs_file_t *file, off_t offset, int whence);
ssize_t  vfsFileClose(vfs_file_t *file);
int vfsFileIoctl(vfs_file_t *file, int req, void *argp);
int vfsFileCanRead(vfs_file_t *file, size_t size);
int vfsFileCanWrite(vfs_file_t *file, size_t size);
int vfsFileEOF(vfs_file_t *file);
int vfsRelative(const char * const rel, const char * const path, char **abs_path);
int vfsLookup(const char *path, uio_t *uio, vfs_vnode_t *vnode, char **abs_path);
int vfsCreat(const char *path, mode_t mode, uio_t *uio, vfs_inode_t **ref);
int vfsmkdir(const char *path, mode_t mode, uio_t *uio, vfs_inode_t **ref);
int vfsmknod(const char *path, uint32_t mode,dev_t dev, uio_t * uio, vfs_inode_t **ref);
int vfsUnlink(const char *path, uio_t *uio);
int vfsStat(vfs_inode_t *inode, stat_t *statbuf);
int vfsPermsCheck(vfs_file_t *file, uio_t * uio);

vfs_path_t *vfsGetMountpoint(char **tokens);
char **canonicalPath(const char * const path);
int vfsParsePath(const char *path, uio_t *uio, char **abs_path);



#endif
