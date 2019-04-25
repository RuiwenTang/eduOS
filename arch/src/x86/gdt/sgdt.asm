
global gdt_flush

; void gdt_flush(gdt_ptr_t*)
gdt_flush:
    mov eax, [esp + 4]      ; gdt_ptr *
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov ax, 0
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush2
flush2:
    ret