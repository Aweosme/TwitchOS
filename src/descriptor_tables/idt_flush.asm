global idt_flush
extern idt_ptr
idt_flush:
	lidt [idt_ptr]		; Flush IDT
	ret

%macro ISR_NOERRCODE 1
global isr%1
isr%1:
	cli
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
global isr%1:
isr%1:
	cli
	push byte %1
	jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern isr_handler
isr_common_stub:
	pusha				; save edi, esi, ebp, esp, ebx, edx, ecx, eax
	mov ax, ds			; lower 16-bits of eax = ds
	push eax			; save the data segment descriptor

	mov ax, 0x10		; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler	; call C interrupt handler

	pop eax				; restore the original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa				; pop saved registers
	add esp, 8			; remove pushed error code and ISR number
	sti
	iret				; return from interrupt
