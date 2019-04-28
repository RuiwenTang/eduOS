#include <eduos/config.h>
#include <eduos/stddef.h>

#include <multiboot/multiboot.h>

#include <asm/gdt.h>
#include <asm/io.h>
#include <asm/vga.h>

int sum_of_three(int arg1, int arg2, int arg3) { return arg1 + arg2 + arg3; }

static void eduos_kernel_init() {
    gdt_install();
    vga_init();
}

void kmain(multiboot_info_t* boot_info) {
    if (boot_info == NULL) {
    } else {
        eduos_kernel_init();
    }

    vga_puts("aaa");

    int a = 10;
    int b = 100;
    if (b % a) {
    }
}