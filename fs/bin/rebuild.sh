#!/bin/sh
/bin/tcc -c -ffreestanding -o /boot/boot.o /src/boot/boot.s
/bin/tcc -c -ffreestanding -o /boot/kernel.o /src/boot/kernel.c
/bin/ld -o /boot/six.bin -T /src/boot/linker.ld /boot/boot.o /boot/kernel.o
/bin/grub-mkrescue -o /dev/sda /

