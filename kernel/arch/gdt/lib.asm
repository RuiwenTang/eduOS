
; void gdt_flush(gdt_ptr_t*)
global gdt_flush
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax
    jmp 0x8:flush2
flush2:
    ret