#include "../include/assert.h"
#include "../include/stdio.h"
#include "../include/stdlib.h"

void __assert(char *mesg){
    puts(mesg);
    puts("-- assertion failed\n");
    abort();
}
