.set	flags, 0b11
.set	magic, 0x1BADB002
.set	checksum, -(magic + flags)

.section .multiboot_header
.align	4
.long	magic
.long	flags
.long	checksum

.section .basic_stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
_start:
	movl	$stack_top, %esp
	call	kernel_main

	cli
	hlt
.halt:
	jmp	.halt

.size _start, . - _start
