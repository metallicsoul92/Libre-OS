CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

BINDIR=../bin/libc




CFLAGS:=$(CFLAGS) -g -ffreestanding -Wall -Wextra

LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

FREEOBJS=\
 src/abort.o\
 src/assert.o\
 src/ctypes.o\
 src/itoa.o\
 src/string.o\
 src/fileimp.o\
 src/stdio.o\
 src/sleep.o\
 src/mem.o\
 src/sys/utsname.o


LIBK_OBJS=$(FREEOBJS:.o=.libk.o)
BINARIES = libk.a


.PHONY: all clean install install-headers install-lib
.SUFFIXES: .o .libk.o .c .S


all: $(BINARIES)

libk.a : $(LIBK_OBJS)
	cd ${BINDIR} && $(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -c $< -o $(BINDIR)/$@ -std=gnu11 $(CFLAGS)

.c.libk.o:
	$(CC) -c $< -o $(BINDIR)/$@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f ${BINDIR}/*.a
	rm -f ${BINDIR}/*.o
	rm -f ${BINDIR}/*/*.o
	rm -f ${BINDIR}/*/*/*.o
	rm -f ${BINDIR}/*.libk.o
	rm -f ${BINDIR}/sys/*.libk.o
