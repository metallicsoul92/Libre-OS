CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

BINDIR=../bin/drivers

DRIVEROBJS=\
ata.o\
fs/vfs/vfs.o\
exec/elf/elf.o

CFLAGS:=$(CFLAGS) -g -ffreestanding -Wall -Wextra



.PHONY: ix86 arm x86_64 clean install-headers clean
.SUFFIXES: .c .o

all: $(DRIVEROBJS)

clean:
	cd ${BINDIR} && rm *.o

.c.o:
	${CC} -c $< -o $(BINDIR)/$@ -std=gnu11 ${CFLAGS}
