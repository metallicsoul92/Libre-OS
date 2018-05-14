#ifndef LIBC_SIGNAL_H
#define LIBC_SIGNAL_H


#ifndef _HAS_PTHREAD
#define _HAS_PTHREAD
typedef int pthread_t;
#endif

#ifndef _HAS_SIZE
#define _HAS_SIZE
typedef unsigned int size_t;
#endif

#ifndef _HAS_UID
#define _HAS_UID
typedef int uid_t;
#endif

#ifndef _HAS_TIMESPEC
#define _HAS_TIMESPEC
struct timespec{
  time_t tv_sec;
  long tv_nsec;
};
#endif

#ifndef _HAS_SIGSET
#define _HAS_SIGSET
typedef unsigned int sigset_t;
#endif

#ifndef _HAS_PID
#define _HAS_PID
typedef int pid_t;
#endif

#ifndef _HAS_PTHREAD_ATTR
#define _HAS_PTHREAD_ATTR
typedef int pthread_attr_t;
#endif

#ifndef _HAS_SIGVAL
#define _HAS_SIGVAL
union sigval{
  int sival_int; //Integer Signal Value
  void *sival_ptr; // Pointer Signal Value
};
#endif

#ifndef _HAS_SIGEVENT
#define _HAS_SIGEVENT
struct sigevent{
  int sigev_notify; //Notification Type
  int sigev_signo; //Signal Number
  union sigval sigev_value; //Signal value
  void (*sigev_notify_function)(union sigval); //Notification Function
  pthread_attr_t *sigev_notify_attributes; //Notification Attributes
};
#endif

#ifndef _HAS_SIGACTION
#define _HAS_SIGACTION
struct sigaction{
  void (*sa_handler)(int);//Pointer to a signal-catching function or
                          //one of the SIG_IGN or SIG_DFL
  sigset_t sa_mask; //Set of signals to be blocked during execution of the
                    //signal handling function
  int sa_flags; //Special Flags
  void (*sa_sigaction)(int,siginfo_t*,void*); //Pointer to a signal
                                              //catching function
};
#endif

#ifndef _HAS_MCONTEXT
#define _HAS_MCONTEXT
typedef unsigned int mcontext_t;
#endif

#ifndef _HAS_STACK
#define _HAS_STACK
struct stack_t{
  void *ss_sp; //Stack base or pointer.
  size_t ss_size; //Stack Size
  int ss_flags; //Flags
};
#endif

#ifndef _HAS_UCONTEXT
#define _HAS_UCONTEXT
struct ucontext_t{
  struct ucontext_t *uc_link; //Pointer to the context that is resumed
  sigset_t uc_sigmask; //The set of signals that are blocked
                      // when this context is active
  struct stack_t uc_stack; // The Stack used by its context
  mcontext_t uc_mcontext; //A Machine Specific representation of
                          //the saved context

};
#endif

#ifndef _HAS_SIGINFO
#define _HAS_SIGINFO
struct siginfo_t{
  int si_signo; //Signal number
  int si_code; //Signal code
  int si_errno; //If non-zero , an errono value associated with this signal
  pid_t si_pid; //Sending Process ID
  void *si_addr; //Address of faulting instruction.
  int si_status; //Exit value or signal.
  long si_band; //Band event for SIGPOLL
  union sigval si_value; //Signal Value
};
#endif

int kill(pid_t,int);
int killpg(pid_t,int);
void psiginfo(const siginfo_t *,const char *);
void psignal(int,const char *);
int pthread_kill(pthread_t, int);
int pthread_sigmask(int,const sigset_t *restrict,sigset_t *restrict);
int raise(int);
int sigaction(int,const struct sigaction *restrict, struct sigaction * restrict);
int sigaddset(sigset_t *,int);
int sigaltstack(const stack_t *restrict, stack_t *restrict);
int sigdelset(sigset_t *,int);
int sigemptyset(sigset_t *);
int sigfillset(sigset_t *);
int sighold(int);
int sigignore(int);
int siginterrupt(int,int);
void (*signal(int,void(*)(int)))(int);
int sigpause(int);
int sigpending(sigset_t *);
int sigprocmask(int,const sigset_t *restrict, sigset_t *restrict);
int sigqueue(pid_t,int,union sigval);
int sigrelse(int);
void (*sigset(int,void(*)(int)))(int);
int sigsuspend(const sigset_t *);
int sigtimedwait(const sigset_t *restrict, siginfo_t *restrict,
                 const struct timespec *restrict);
int sigwait(const sigset_t *restrict, int *restrict);
int sigwaitinfo(const sigset_t *restrict, siginfo_t *restrict);


#endif
