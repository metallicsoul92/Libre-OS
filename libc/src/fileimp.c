#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/stddef.h"


unsigned char stdinWriteBuff[1024];
unsigned char stdoutReadBuff[1024];
unsigned char stderrReadBuff[1024];


unsigned char stdinPreBuff[1024];
unsigned char stdoutPreBuff[1024];
unsigned char stderrPreBuff[1024];


struct __IO_FILE _stdin={
    ._flags = 0,
    ._read_ptr =0,
    ._read_end=0,
    ._read_base=0,

    ._write_ptr =&stdinWriteBuff,
    ._write_end=&stdinWriteBuff[1024],
    ._write_base=&stdinWriteBuff,

    ._buf_base=&stdinPreBuff,
    ._buf_end=&stdinPreBuff[1024],

    ._save_base=0,
    ._backup_base=0,
    ._save_end=0,
    ._markers=0,

    ._chain = 0,
    ._fileno=0,
    ._old_offset=0,
    ._lock = 0
};

struct __IO_FILE _stdout={
    ._flags = 0,
    ._read_ptr =&stdoutReadBuff,
    ._read_end=&stdoutReadBuff[1024],
    ._read_base=&stdoutReadBuff,

    ._write_ptr =0,
    ._write_end=0,
    ._write_base=0,

    ._buf_base=&stdoutPreBuff,
    ._buf_end=&stdoutPreBuff[1024],

    ._save_base=0,
    ._backup_base=0,
    ._save_end=0,
    ._markers=0,

    ._chain = &_stdin,
    ._fileno=1,
    ._old_offset=0,
    ._lock = 0
};

struct __IO_FILE _stderr={
    ._flags = 0,
    ._read_ptr =&stderrReadBuff,
    ._read_end=&stderrReadBuff[1024],
    ._read_base=&stderrReadBuff,

    ._write_ptr =0,
    ._write_end=0,
    ._write_base=0,

    ._buf_base=&stderrPreBuff,
    ._buf_end=&stderrPreBuff[1024],

    ._save_base=0,
    ._backup_base=0,
    ._save_end=0,
    ._markers=0,


    ._chain = &_stdout,
    ._fileno=2,
    ._old_offset=0,
    ._lock = 0
};
