
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp bin/kernel.ix86 isodir/boot/libreOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "LibreOS" {
	multiboot /boot/libreOS.kernel
}
EOF
grub-mkrescue -o LibreOS.iso isodir
