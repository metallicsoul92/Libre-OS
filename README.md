# Libre-OS

  A Free Posix Compliant Operating System based on Unix and Linux philosophies
as well as the philosophies of The GNU Project.


# Requirements to build
    An i686-elf-gcc cross compiler. (unless your using an actual i686 processor)
    xorriso
    Make

# To Install
   First you may want to run the configure script. At the moment it  is targeted
to Intel's x86 architecture , so i setup a build script as well in the scripts
folder. Also you may want to generate the bin directory or else there will be
build errors. I have a script in there for that


    cd scripts/
    ./genbindir.sh
    ./configure.sh
    ./build-ix86.sh



# To Run

  I personally use qemu. after building , assuming we are still in the scripts
directory, i normally test by using:

  qemu-system-i386 -d int --cdrom  ../LibreOS.iso

  This triggers qemu to display information about the registers while running


# TODO:

  1. Setup Page allocations and more memory management (mmap and sbrk maybe?)
  2. Correctly setup processes
  3. Create User-Mode and add support for Ext4 file system
     a. Ext4 has backwards compatibility to Ext3 and Ext2 from what i read.
        so i do believe that i can load those three if i just implement one
