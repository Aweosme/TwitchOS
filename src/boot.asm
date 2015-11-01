section .boot			; flags for all our multibooting needs
MBALIGN	equ 1<<0		; Is this just convention to define this way?
				; Yeah it is just how everyone does it
MEMINFO		equ 1<<1
FLAGS		equ MBALIGN | MEMINFO
MAGIC			equ 0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

				; Multiboot Header - For bootloaders supporting
				; multiboot (Contents defined above)
section .multiboot		; give this stuff its own section
align 4
	dd	MAGIC
	dd	FLAGS
	dd	CHECKSUM

section .bss			; A stack (We need one, otherwise the C won't work :( )!
align 4				; We might eventually want a bigger stack.
stack_bottom:
resb 8192
stack_top:			; Stacks grow down

section .text			; this is where stuff starts to happen
global _start			; make our _start function public
_start:				; start doing things
	mov esp, stack_top
	extern kernel_main	; tell the computer (*compiler) that we have a
				; function called kernel_main but its not defined here
	call kernel_main	; call kernel_main from main.c

	cli			; disable interrupts

.halt:
	hlt			; wait for an interrupt (not gonna happen)
	jmp .halt		; just in case, jump back to the halt label
