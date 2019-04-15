#ifndef LIBC_AIO_H
#define LIBC_AIO_H 1


#ifndef HAS_AIOCB
struct _aiocb{
  int             aio_fildes; //File descriptor.
  off_t           aio_offset; //File offset.
  volatile void  *aio_buf; //Location of buffer.
  size_t          aio_nbytes; //Length of transfer.
  int             aio_reqprio; //Request priority offset.
  struct sigevent aio_sigevent; //Signal number and value.
  int             aio_lio_opcode; //Operation to be performed
};
#define HAS_AIOCB 1
#endif

#define AIO_ALLDONE 1
#define AIO_CANCELLED 2
#define AIO_NOTCANCELLED 4
#define LIO_NOP 8
#define LIO_NOWAIT 16
#define LIO_READ 32
#define LIO_WRITE 64


int      aio_cancel(int , struct aiocb *);
int      aio_error(const struct aiocb *);
int      aio_fsync(int,struct aiocb *);
int      aio_read(struct aiocb *);
ssize_t  aio_return(struct aiocb *);
int      aio_suspend(const struct aiocb *const [], int, const struct timespec *);
int      aio_write(struct aiocb *);
int      lio_listio(int,struct aiocb *restrict const [restrict], int, struct sigevent * restrict);

#endif
