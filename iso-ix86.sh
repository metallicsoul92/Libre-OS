
mkdir -p isodir
mkdir -p isodir/bin
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
mkdir -p isodir/dev
mkdir -p isodir/etc
mkdir -p isodir/etc/X11
mkdir -p isodir/home
mkdir -p isodir/lib
mkdir -p isodir/lib/libk
mkdir -p isodir/lib/libc
mkdir -p isodir/lib32
mkdir -p isodir/lib64
mkdir -p isodir/media
mkdir -p isodir/opt
mkdir -p isodir/proc
mkdir -p isodir/root
mkdir -p isodir/sbin
mkdir -p isodir/srv
mkdir -p isodir/sys
mkdir -p isodir/temp
mkdir -p isodir/usr
mkdir -p isodir/usr/bin
mkdir -p isodir/usr/include
mkdir -p isodir/usr/include/libk
mkdir -p isodir/usr/include/kernel
mkdir -p isodir/usr/include/kernel/arch
mkdir -p isodir/usr/lib
mkdir -p isodir/usr/lib32
mkdir -p isodir/usr/lib64
mkdir -p isodir/usr/local
mkdir -p isodir/usr/sbin
mkdir -p isodir/usr/share
mkdir -p isodir/usr/src
mkdir -p isodir/usr/X11R6
mkdir -p isodir/var
mkdir -p isodir/var/cache
mkdir -p isordir/var/lib
mkdir -p isodir/var/lock
mkdir -p isodir/var/log
mkdir -p isodir/var/mail
mkdir -p isodir/var/opt
mkdir -p isodir/var/run
mkdir -p isodir/var/spool
mkdir -p isodir/var/spool/mail
mkdir -p isodir/var/tmp


cp bin/kernel.ix86 isodir/boot/libreOS.kernel
cp bin/libc/libk.a isodir/lib/libk/libk.a

cp arch/iX86/*.h isodir/usr/include/kernel/arch/
cp -r include/* isodir/usr/include/kernel/
cp -r libc/include/* isodir/usr/include/libk/

cat > isodir/boot/grub/grub.cfg << EOF
menuentry "LibreOS" {
	multiboot /boot/libreOS.kernel
}
EOF
grub-mkrescue -o LibreOS.iso isodir
