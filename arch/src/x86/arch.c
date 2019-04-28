#include <asm/arch.h>
#include <asm/gdt.h>
#include <asm/vga.h>

void arch_init() {
    gdt_setup();
    vga_init();
    char str[] = "init gdt";
    vga_puts(str);
}