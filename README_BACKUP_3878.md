# Libre-OS

  A Free Posix Compliant Operating System based on Unix and Linux philosophies
as well as the philosophies of The GNU Project.


<<<<<<< HEAD
#Requirements to build
    an i686-elf-gcc cross compiler. (unless your using an actual i686 processor)

#To Install
=======
# Requirements to build
    an i686-elf-gcc cross compiler. (unless your using an actual i686 processor)

# To Install
>>>>>>> acc6407069823ddff04399d99471a0b2e35cb881
  first you may want to run the configure script. At the moment it  is targetted
to intel's x86 architecture , so i setup a build script as well in the scripts folder.


    cd scripts/
    ./configure.sh
    ./build-ix86.sh


<<<<<<< HEAD
#To Run
=======
# To Run
>>>>>>> acc6407069823ddff04399d99471a0b2e35cb881

  I personally use qemu. after building , assumming we are still in the scripts
directory, i normally test by using:

  qemu-system-i386 -d int --cdrom  ../LibreOS.iso

  This triggers qemu to display information about the registers while running
<<<<<<< HEAD
  
#TODO:
=======

# TODO:
>>>>>>> acc6407069823ddff04399d99471a0b2e35cb881
  Correctly setup paging.
  Correctly setup processes
  Create User-Mode and add support for Ext4 file system
      Ext4 has backwards compatibility to Ext3 and Ext2 from what i read.
    so i do believe that i can load those three if i just implement one
