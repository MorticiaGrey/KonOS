#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/konos.kernel isodir/boot/konos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "konos" {
	multiboot /boot/konos.kernel
}
EOF
grub-mkrescue -o konos.iso isodir
