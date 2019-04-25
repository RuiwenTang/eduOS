#include <asm/arch.h>
#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/irq.h>
#include <asm/vga.h>

void* isyscall_handler = 0;

void arch_init() {
    vga_init();
    gdt_setup();
    idt_setup();

    asm volatile("int $0x3");
}

void arch_registe_syscall(void* call_handler) {
    isyscall_handler = call_handler;
}

void arch_registe_irq_call(uint32_t index, irq_handler_t handler);