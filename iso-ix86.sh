
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
mkdir -p isodir/lib/libk
mkdir -p isodir/lib/libc
mkdir -p isodir/usr
mkdir -p isodir/usr/include
mkdir -p isodir/usr/include/libk
mkdir -p isodir/usr/include/kernel
mkdir -p isodir/usr/include/kernel/arch
mkdir -p isodir/proc
mkdir -p isodir/tmp
mkdir -p isodir/dev


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
