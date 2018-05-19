#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/stddef.h"

struct __IO_FILE _stdin={
    ._flags = 0,
    ._read_ptr =0,
    ._read_end=0,
    ._read_base=0,

    ._write_ptr =0,
    ._write_end=0,
    ._write_base=0,

    ._buf_base=0,
    ._buf_end=0,

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
    ._read_ptr =0,
    ._read_end=0,
    ._read_base=0,

    ._write_ptr =0,
    ._write_end=0,
    ._write_base=0,

    ._buf_base=0,
    ._buf_end=0,

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
    ._read_ptr =0,
    ._read_end=0,
    ._read_base=0,

    ._write_ptr =0,
    ._write_end=0,
    ._write_base=0,

    ._buf_base=0,
    ._buf_end=0,

    ._save_base=0,
    ._backup_base=0,
    ._save_end=0,
    ._markers=0,


    ._chain = &_stdout,
    ._fileno=2,
    ._old_offset=0,
    ._lock = 0
};
