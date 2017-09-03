CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

BINDIR=../bin/kernel
ARCHDIR=../arch

KERNOBJS=\
tty.o\
kernel.o\

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra



.PHONY: ix86 arm x86_64 clean install-headers clean
.SUFFIXES: .c .o


ix86: $(KERNOBJS)
	cd ${ARCHDIR}/iX86 && make

clean:
	cd ${BINDIR}/asm && rm *
	cd ${BINDIR} && rm *.o

.c.o:
	${CC} -c $< -o $(BINDIR)/$@ -std=gnu11 ${CFLAGS}
