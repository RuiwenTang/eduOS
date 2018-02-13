[BITS 16]
    org 0x7c00

Entry16:
    ; when in real mode disable interrupt, prevent timer interrupt to make system crash
    cli

    mov eax, esp
    mov [saveESP], eax      ; save current esp, so we can return to protect mode
    sgdt [save_gdt]         ; save protectect mode gdtr
    sidt [saveIDT]          ; save protected mode idtr

    mov eax, 0x30
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax

    mov eax, cr0
    mov [savcr0], eax       ; save protect mode cr0
    and eax, 0x7FFFFFFE     ; clear PE bit, and back to real mode
    mov cr0, eax

    jmp 0: GoRMode          ; use jmp to change cs value, and now we can run real mode code

GoRMode:
    mov sp, StackTop        ; setup real mode stack, to use BIOS interrupt
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    lidt [idt_real]         ; load real mode idt

    sti

;     follow code will use BIOS int 10 to change video mode
;     mov ax, 0x4F02	; set VBE mode
;     mov bx, 0x4118	; VBE mode number; notice that bits 0-13 contain the mode number and bit 14 (LFB) is set and bit 15 (DM) is clear.
;     int 0x10			; call VBE BIOS
;     cmp ax, 0x004F	; test for error
;     jne error

; .s1:
;     jmp .s1

    call display_msg
    ; prepare back to protect mode load proctect mode gdtr and idtr
    lgdt [save_gdt]
    lidt [saveIDT]

    mov eax, [savcr0]       ; reset cr0 to protect mode
    mov cr0, eax

    mov eax, 0x10           ; set protect mode data selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov eax, [saveESP]      ; reset protect mode esp
    mov esp, eax

    jmp dword 0x08 : 0x150000   ; far jmp to protect mode

error:
    jmp error

display_msg:
    mov ax, STR
    mov bp, ax
    mov cx, 17
    mov ax, 0x1301
    mov bx, 0x000c
    mov dh, 1
    mov dl, 0
    int 10h
    ret

STR: db "Hello Real Model!"

idt_real:
    dw 0x3ff        ; 256 entries, 4b each = 1K
    dd 0            ; Real Mode IVT @ 0x0000


savcr0:
    dd 0

saveESP:
    dd 0

saveIDT:
    dw 0
    dd 0

save_gdt:
    dw 0
    dd 0

stack:
    times 128 db 0
StackTop equ $ - stack - 1

times 512 - ($ - $$) db 0
