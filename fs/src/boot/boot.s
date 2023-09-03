.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
_start:
.global _start
.type _start, @function
	mov $stack_top, %esp
	call kernel_main
	jmp .

.global inb
.type inb, @function
inb:
  mov 4(%esp), %edx
  in %dx, %al
  ret

.global inw
.type inw, @function
inw:
  mov 4(%esp), %edx
  in %dx, %ax
  ret

.global outb
.type outb, @function
outb:
  mov 4(%esp), %edx
  mov 8(%esp), %al
  out %al, %dx
  ret

.size _start, . - _start

