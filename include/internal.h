#ifndef _INTERNAL_H_
#define _INTERNAL_H_


/*
 * Internal Kernel Version:
 * Contains information about the Kernel versioning
 *
 */

struct __internal_kernel_version{
    unsigned short maj;
    unsigned short min;
    unsigned short bug;
    unsigned short tweak;
};

typedef struct __internal_kernel_version _internal_kernel_version;

/*
 * Internal Kernel Name:
 * Contains the name for the Kernel
 * Version name changes on each update, but the name will be used for uname
 */

struct __internal_kernel_name{
    char  name[16];
    char versionName[32];
};
typedef struct __internal_kernel_name _internal_kernel_name;
/*
 * Internal Kernel Info:
 * Contains information about the Kernel
 *
 */

typedef struct {
    _internal_kernel_name name;
    _internal_kernel_version version;
} _internal_kernel_info;







#endif // Internal.h
