#include "../../../include/drivers/fs/vfs/vfs.h"
#include "../../../include/tty.h"
#include "../../../libc/include/string.h"
#include "../../../libc/include/errno.h"


list_fs_t *registered_fs = NULL;
vfs_inode_t *vfs_root = NULL;
vfs_node_t vfs_node = { .name="/"};

//utility Function
char **tokenize(const char *s, char c)
{
    if (s == NULL || *s == '\0')
        return NULL;

    while (*s == c)
        ++s;

    char *tokens = strdup(s);

    if (tokens == NULL)
        return NULL;

    int len = strlen(s);

    if (!len) {
        char **ret = kmalloc(sizeof(char *));
        *ret = NULL;
        return ret;
    }

    int i, count = 0;
    for (i = 0; i < len; ++i) {
        if (tokens[i] == c) {
            tokens[i] = 0;
            ++count;
        }
    }

    if (s[len-1] != c)
        ++count;

    char **ret = kmalloc(sizeof(char *) * (count + 1));

    int j = 0;
    ret[j++] = tokens;

    for (i = 0; i < strlen(s) - 1; ++i)
        if (tokens[i] == 0)
            ret[j++] = &tokens[i+1];

    ret[j] = NULL;

    return ret;
}


/*Functions*/
void vfsInit(void){
  printk("Initializing Registered File System List\n");
}
int vfsInstall(fs_t * fs){
  list_fs_t * install = kmalloc(sizeof(list_fs_t));
  install->name = fs->name;
  install->fs = fs;
  install->next = registered_fs;
  registered_fs = install;
  printk("Registered Filesystem : %s\n", registered_fs->name);
  return 0;
}

void vfsMountRoot(vfs_inode_t *inode){
    //TODO: Implement this!
    vfs_root = inode;
    vfs_node.iref = inode;
    vfs_node.children = NULL;
    printk("vfs mounted at: %s\n",vfs_node.name);

 }
int vfsBind(const char * path, vfs_inode_t *target){
    //TODO: Implement this!
    return -1;
 }
int vfsMount(const char *type, const char *dir, int flags, void *data,uio_t *uio){
    //TODO: Implement this!
    return -1;
 }

//vnode Data
int vfsVmknod(vfs_vnode_t * dir, const char *fn, uint32_t mode, dev_t dev,
              uio_t *uio, vfs_inode_t **ref){
                  //TODO: Implement this!
                  return -1;
               }
int vfsVmcreat(vfs_vnode_t * dir, const char *fn, uio_t *uio, vfs_inode_t **ref){
    //TODO: Implement this!
    return -1;
 }
int vfsVmkdir(vfs_vnode_t *dir, const char *dname, uio_t *uio, vfs_inode_t **ref){
    //TODO: Implement this!
    return -1;
 }
int vfsVunlink(vfs_vnode_t *dir, const char *fn, uio_t * uio){
    //TODO: Implement this!
    return -1;
 }
int vfsVfind(vfs_vnode_t * vnode, const char * name , vfs_vnode_t * child){
    //TODO: Implement this!
    return -1;
 }
int vfsVget(vfs_vnode_t *vnode, vfs_inode_t **inode){
    //TODO: Implement this!
    return -1;
 }

int vfsMap(vm_entry_t * entry){
    //TODO: Implement this!
    return -1;
 }

ssize_t vfsRead(vfs_inode_t *inode,off_t offset, size_t size, void *buffer){
    //TODO: Implement this!
    return -1;
 }
ssize_t vfsWrite(vfs_inode_t *inode,off_t offset, size_t size, void *buffer){
    //TODO: Implement this!
    return -1;
 }
ssize_t vfsReaddir(vfs_inode_t *inode, off_t offset, vfs_dirent_t *dirent){
    //TODO: Implement this!
    return -1;
 }
int vfsIoctl(vfs_inode_t *inode, unsigned long req, void *argp){
    //TODO: Implement this!
    return -1;
 }
int vfsClose(vfs_inode_t *inode){
    //TODO: Implement this!
    return -1;
 }
int vfsTrunc(vfs_inode_t *inode, off_t len){
    //TODO: Implement this!
    return -1;
 }
int vfsFileOpen(vfs_file_t *file){
    //TODO: Implement this!
    return -1;
 }
ssize_t vfsFileRead(vfs_file_t *file, void *buffer, size_t size){
    //TODO: Implement this!
    return -1;
 }
ssize_t vfsFileWrite(vfs_file_t *file, void *buffer, size_t size){
    //TODO: Implement this!
    return -1;
 }
ssize_t vfsFileReaddir(vfs_file_t *file,vfs_dirent_t *dirent){
    //TODO: Implement this!
    return -1;
 }
off_t vfsFileLseek(vfs_file_t *file, off_t offset, int whence){
    //TODO: Implement this!
    return -1;
 }
ssize_t  vfsFileClose(vfs_file_t *file){
    //TODO: Implement this!
    return -1;
 }
int vfsFileIoctl(vfs_file_t *file, int req, void *argp){
    //TODO: Implement this!
    return -1;
 }
int vfsFileCanRead(vfs_file_t *file, size_t size){
    //TODO: Implement this!
    return -1;
 }
int vfsFileCanWrite(vfs_file_t *file, size_t size){
    //TODO: Implement this!
    return -1;
 }
int vfsFileEOF(vfs_file_t *file){
    //TODO: Implement this!
    return -1;
 }
int vfsRelative(const char * const rel, const char * const path, char **abs_path){
    //TODO: Implement this!
    return -1;
 }
int vfsLookup(const char *path, uio_t *uio, vfs_vnode_t *vnode, char **abs_path){
    //TODO: Implement this!
    return -1;
 }
int vfsCreat(const char *path, mode_t mode, uio_t *uio, vfs_inode_t **ref){
    //TODO: Implement this!
    return -1;
 }
int vfsmkdir(const char *path, mode_t mode, uio_t *uio, vfs_inode_t **ref){
    //TODO: Implement this!
    return -1;
 }
int vfsmknod(const char *path, uint32_t mode,dev_t dev, uio_t * uio, vfs_inode_t **ref){
    //TODO: Implement this!
    return -1;
 }
int vfsUnlink(const char *path, uio_t *uio){
    //TODO: Implement this!
    return -1;
 }
int vfsStat(vfs_inode_t *inode, stat_t *statbuf){
    statbuf->st_dev = inode->device;
    statbuf->st_ino = inode->ino;
    statbuf->st_mode = inode->mode;
    statbuf->st_nlink = inode->nlink;
    statbuf->st_uid = inode->uid;
    statbuf->st_gid = inode->gid;
    statbuf->st_rdev = inode->rdevice;
    statbuf->st_mtim = inode->mtime;
    statbuf->st_atim = inode->atime;
    statbuf->st_ctim = inode->ctime;
    statbuf->st_blksize = inode->size;

    return 0;
 }
int vfsPermsCheck(vfs_file_t *file, uio_t * uio){
    //TODO: Implement this!
    return -1;
 }

vfs_path_t *vfsGetMountpoint(char **tokens){
    //TODO: Implement this!
    return -1;
 }
char **canonicalPath(const char * const path){
  char **results = tokenize(path,'/');
    return results;
 }
int vfsParsePath(const char *path, uio_t *uio, char **abs_path){
    //TODO: Implement this!
    return -1;
 }
