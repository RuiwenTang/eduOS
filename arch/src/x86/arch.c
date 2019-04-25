#include <asm/arch.h>
#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/vga.h>

void arch_init() {
    vga_init();
    gdt_setup();
    idt_setup();

    asm volatile("int $0x3");
}