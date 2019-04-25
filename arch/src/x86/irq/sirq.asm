; c function to handle interrupt
extern isr_handler

;define a macro, taking one parameter
%macro ISR_NOERRCODE 1
[global isr%1]
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
[global isr%1]
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

; NASM macro for asynchronous interrupts (no exceptions)
%macro irqstub 1
    global irq%1
    irq%1:
        push byte 0 ; pseudo error code
        push byte 32+%1
        jmp isr_common_stub
%endmacro

global apic_timer
apic_timer:
	push byte 0 ; pseudo error code
	push byte 123
	jmp isr_common_stub

global apic_lint0
apic_lint0:
	push byte 0 ; pseudo error code
	push byte 124
	jmp isr_common_stub

global apic_lint1
apic_lint1:
	push byte 0 ; pseudo error code
	push byte 125
	jmp isr_common_stub

global apic_error
apic_error:
	push byte 0 ; pseudo error code
	push byte 126
	jmp isr_common_stub

global apic_svr
apic_svr:
	push byte 0 ; pseudo error code
	push byte 127
	jmp isr_common_stub

global cr3_save
cr3_save:
    dd 0

; Used to realize system calls.
; By entering the handler, the interrupt flag is not cleared.
global isrsyscall
isrsyscall:
    cli
    push es
    push ds
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax

; Set kernel data segmenets
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov eax, [esp]
    sti

    extern isyscall_handler
    call isyscall_handler

    cli
    add esp, 4 ; eax contains the return value
               ; => we did not restore eax

    pop ebx
    pop ecx
    pop edx
    pop esi
    pop edi
    pop ebp
    pop ds
    pop es
    sti
    iret

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha                           ; pushes edi, esi, ebp, esp, ebx, edx, ecx, eax
    mov ax, ds                      ; Lower 16-bits of eax = ds
    push eax

    mov ax, 0x10                    ; kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_handler
    add esp, 4

    cmp eax, 0
    je .no_context_switch


.no_context_switch:
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                            ; pops edi, esi, ebp
    add esp, 8
    sti
    iret                            ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
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
