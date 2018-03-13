# Libre-OS

  A Free Posix Compliant Operating System based on Unix and Linux philosophies
as well as the philosophies of The GNU Project.


# Requirements to build
    an i686-elf-gcc cross compiler. (unless your using an actual i686 processor)

# To Install
   first you may want to run the configure script. At the moment it  is targetted
to intel's x86 architecture , so i setup a build script as well in the scripts folder.


    cd scripts/
    ./configure.sh
    ./build-ix86.sh



# To Run

  I personally use qemu. after building , assumming we are still in the scripts
directory, i normally test by using:

  qemu-system-i386 -d int --cdrom  ../LibreOS.iso

  This triggers qemu to display information about the registers while running
  

# TODO:

  Correctly setup paging.
  Correctly setup processes
  Create User-Mode and add support for Ext4 file system
      Ext4 has backwards compatibility to Ext3 and Ext2 from what i read.
    so i do believe that i can load those three if i just implement one
