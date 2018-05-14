#ifndef LIBC_SYS_TYPES_H_
#define LIBC_SYS_TYPES_H_

#ifndef _HAS_BLKCNT
#define _HAS_BLKCNT
typedef int blkcnt_t;
#endif

#ifndef _HAS_BLKSIZE
#define _HAS_BLKSIZE
typedef int blksize_t;
#endif

#ifndef _HAS_CLOCK
#define _HAS_CLOCK
typedef int clock_t;
#endif

#ifndef _HAS_CLOCKID
#define _HAS_CLOCKID
typedef int clockid_t;
#endif

#ifndef _HAS_DEV
#define _HAS_DEV
typedef int dev_t;
#endif

#ifndef _HAS_FSBLKCNT
#define _HAS_FSBLKCNT
typedef unsigned int fsblkcnt_t;
#endif

#ifndef _HAS_FSFILCNT
#define _HAS_FSFILCNT
typedef unsigned int fsfilcnt_t;
#endif

#ifndef _HAS_GID
#define _HAS_GID
typedef int gid_t;
#endif

#ifndef _HAS_ID
#define _HAS_ID
typedef int id_t;
#endif

#ifndef _HAS_INO
#define _HAS_INO
typedef unsigned int ino_t;
#endif

#ifndef _HAS_KEY
#define _HAS_KEY
typedef int key_t;
#endif

#ifndef _HAS_MODE
#define _HAS_MODE
typedef int mode_t;
#endif

#ifndef _HAS_NLINK
#define _HAS_NLINK
typedef int nlink_t;
#endif

#ifndef _HAS_OFF
#define _HAS_OFF
typedef int off_t;
#endif

#ifndef _HAS_PID
#define _HAS_PID
typedef int pid_t;
#endif

#ifndef _HAS_PTHREAD_ATTR
#define _HAS_PTHREAD_ATTR
typedef int pthread_attr_t;
#endif

#ifndef _HAS_PTHREAD_BARRIER
#define _HAS_PTHREAD_BARRIER
typedef int pthread_barrier_t;
#endif

#ifndef _HAS_PTHREAD_BARRIERATTR
#define _HAS_PTHREAD_BARRIERATTR
typedef int pthread_barrierattr_t;
#endif

#ifndef _HAS_PTHREAD_COND
#define _HAS_PTHREAD_COND
typedef int pthread_cond_t;
#endif

#ifndef _HAS_PTHREAD_CONDATTR
#define _HAS_PTHREAD_CONDATTR
typedef int pthread_condattr_t;
#endif

#ifndef _HAS_PTHREAD_KEY
#define _HAS_PTHREAD_KEY
typedef int pthread_key_t;
#endif

#ifndef _HAS_PTHREAD_ATTR
#define _HAS_PTHREAD_ATTR
typedef int pthread_attr_t;
#endif

#ifndef _HAS_PTHREAD_MUTEX
#define _HAS_PTHREAD_MUTEX
typedef int pthread_mutex_t;
#endif

#ifndef _HAS_PTHREAD_MUTEXATTR
#define _HAS_PTHREAD_MUTEXATTR
typedef int pthread_mutexattr_t;
#endif

#ifndef _HAS_PTHREAD_ONCE
#define _HAS_PTHREAD_ONCE
typedef int pthread_once_t;
#endif

#ifndef _HAS_PTHREAD_RWLOCK
#define _HAS_PTHREAD_RWLOCK
typedef int pthread_rwlock_t;
#endif

#ifndef _HAS_PTHREAD_RWLOCKATTR
#define _HAS_PTHREAD_RWLOCKATTR
typedef int pthread_rwlockattr_t;
#endif

#ifndef _HAS_PTHREAD_SPINLOCK
#define _HAS_PTHREAD_SPINLOCK
typedef int pthread_spinlock_t;
#endif

#ifndef _HAS_PTHREAD
#define _HAS_PTHREAD
typedef int pthread_t;
#endif

#ifndef _HAS_SIZE
#define _HAS_SIZE
typedef unsigned int size_t;
#endif

#ifndef _HAS_SSIZE
#define _HAS_SSIZE
typedef int ssize_t;
#endif

#ifndef _HAS_SUSECONDS
#define _HAS_SUSECONDS
typedef int suseconds_t;
#endif

#ifndef _HAS_TIME
#define _HAS_TIME
typedef int time_t;
#endif

#ifndef _HAS_TIMER
#define _HAS_TIMER
typedef int timer_t;
#endif

#ifndef _HAS_TRACE_ATTR
#define _HAS_TRACE_ATTR
typedef int trace_attr_t;
#endif

#ifndef _HAS_TRACE_EVENT_ID
#define _HAS_TRACE_EVENT_ID
typedef int trace_event_id_t;
#endif

#ifndef _HAS_TRACE_EVENT_SET
#define _HAS_TRACE_EVENT_SET
typedef int trace_event_set_t;
#endif

#ifndef _HAS_TRACE_ID
#define _HAS_TRACE_ID
typedef int trace_id_t;
#endif

#ifndef _HAS_UID
#define _HAS_UID
typedef int uid_t;
#endif

#endif
