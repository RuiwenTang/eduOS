
global idt_flush

; void idt_flush(idt_ptr_t*)
idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret