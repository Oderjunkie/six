#!/bin/sh
set -xe

./i686-elf/tcc -m32 -c -ffreestanding -o ./fs/boot/boot.o ./fs/src/boot/boot.s
./i686-elf/tcc -m32 -O0 -c -ffreestanding -o ./fs/boot/kernel.o ./fs/src/boot/kernel.c
ld -melf_i386 -o ./fs/boot/six.bin -T ./fs/src/boot/linker.ld ./fs/boot/boot.o ./fs/boot/kernel.o
grub-mkrescue -p /boot -o ./six.iso ./fs

