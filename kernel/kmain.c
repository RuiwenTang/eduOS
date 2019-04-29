#include <eduos/config.h>
#include <eduos/stddef.h>
#include <eduos/stdio.h>

#include <multiboot/multiboot.h>

#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/vga.h>

int sum_of_three(int arg1, int arg2, int arg3) { return arg1 + arg2 + arg3; }

static void eduos_kernel_init() {
    gdt_install();
    vga_init();
    idt_install();
    irq_init();
}

void kmain(multiboot_info_t* boot_info) {
    if (boot_info == NULL) {
    } else {
        eduos_kernel_init();
    }

    kprintf("Hello World kernel %d !", 123);

    int a = 10;
    int b = 100;
    if (b % a) {
    }
}