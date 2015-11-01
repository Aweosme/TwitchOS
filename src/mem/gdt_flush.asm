; This file sets changes the GDT (Global Descriptor Table)
global gdt_flush		; Allows the C code to link to this
extern gdt_ptr			;
gdt_flush:
	lgdt [gdt_ptr]		; Load the GDT with our '_gp' which is a special pointer
	mov ax, 0x10		; 0x10 is the offset in the GDT to our data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:jump_back	; 0x08 is the offset to our code segment: Far jump!
jump_back:
	ret					; Returns back to the C code!
