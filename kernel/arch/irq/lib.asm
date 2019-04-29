; The first 32 interrupt service routines (ISR) entries correspond to exceptions.
; Some exceptions will push an error code onto the stack which is specific to
; the exception caused. To decrease the complexity, we handle this by pushing a
; Dummy error code of 0 onto the stack for any ISR that doesn't push an error
; code already.
;
; ISRs are registered as "Interrupt Gate".
; Therefore, the interrupt flag (IF) is already cleared.

; NASM macro which pushs also an pseudo error code
%macro isrstub_pseudo_error 1
    global isr%1
    isr%1:
        push byte 0 ; pseudo error code
        push byte %1
        jmp common_stub
%endmacro

; Similar to isrstub_pseudo_error, but without pushing
; a pseudo error code => The error code is already
; on the stack.
%macro isrstub 1
    global isr%1
    isr%1:
        push byte %1
        jmp common_stub
%endmacro

; Create isr entries, where the number after the
; pseudo error code represents following interrupts:
; 0: Divide By Zero Exception
; 1: Debug Exception
; 2: Non Maskable Interrupt Exception
; 3: Int 3 Exception
; 4: INTO Exception
; 5: Out of Bounds Exception
; 6: Invalid Opcode Exception
; 7: Coprocessor Not Available Exception
%assign i 0
%rep    8
    isrstub_pseudo_error i
%assign i i+1
%endrep

; 8: Double Fault Exception (With Error Code!)
isrstub 8

; 9: Coprocessor Segment Overrun Exception
isrstub_pseudo_error 9

; 10: Bad TSS Exception (With Error Code!)
; 11: Segment Not Present Exception (With Error Code!)
; 12: Stack Fault Exception (With Error Code!)
; 13: General Protection Fault Exception (With Error Code!)
; 14: Page Fault Exception (With Error Code!)
%assign i 10
%rep 5
    isrstub i
%assign i i+1
%endrep

; 15: Reserved Exception
; 16: Floating Point Exception
; 17: Alignment Check Exception
; 18: Machine Check Exceptio
; 19-31: Reserved
%assign i 15
%rep    17
    isrstub_pseudo_error i
%assign i i+1
%endrep

; NASM macro for asynchronous interrupts (no exceptions)
%macro irqstub 1
    global irq%1
    irq%1:
        push byte 0 ; pseudo error code
        push byte 32+%1
        jmp common_stub
%endmacro

; Create entries for the interrupts 0 to 23
%assign i 0
%rep    24
    irqstub i
%assign i i+1
%endrep

extern irq_handler
extern get_current_stack
extern finish_task_switch

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

    extern syscall_handler
    call syscall_handler

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

; Create a pseudo interrupt on top of the stack.
; Afterwards, we switch to the task with iret.
; We already are in kernel space => no pushing of SS required.
global switch_context
ALIGN 4
switch_context:
    mov eax, [esp+4]            ; on the stack is already the address to store the old esp
    pushf                       ; push controll register
    push DWORD 0x8              ; CS
    push DWORD rollback         ; EIP
    push DWORD 0x0              ; Interrupt number
    push DWORD 0x00edbabe       ; Error code
    pusha                       ; push all general purpose registers...
    push 0x10                   ; kernel data segment (for ES)
    push 0x10                   ; kernel data segment (for DS)

    jmp common_switch

ALIGN 4
rollback:
    ret

ALIGN 4
common_stub:
    pusha
    push es
    push ds
    mov ax, 0x10
    mov es, ax
    mov ds, ax

; Use the same handler for interrupts and exceptions
    push esp
    call irq_handler
    add esp, 4

    cmp eax, 0
    je no_context_switch

common_switch:
    mov [eax], esp             ; store old esp
    call get_current_stack     ; get new esp
    xchg eax, esp

; Set task switched flag
    mov eax, cr0
    or eax, 8
    mov cr0, eax

; Set esp0 in the task state segment
    extern set_kernel_stack
    call set_kernel_stack

; Call cleanup code
    call finish_task_switch

no_context_switch:
    pop ds
    pop es
    popa
    add esp, 8
    iret
