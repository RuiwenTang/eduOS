#include <eduos/config.h>
#include <eduos/stddef.h>
#include <eduos/string.h>

#include <multiboot/multiboot.h>

#ifdef CONFIG_X86_32
#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/io.h>
#include <asm/v86.h>
#include <asm/vga.h>
#endif

int sum_of_three(int arg1, int arg2, int arg3) { return arg1 + arg2 + arg3; }

static void eduos_kernel_init() {
#ifdef CONFIG_X86_32
    gdt_install();
    idt_install();
    vga_init();
#endif
}

void kmain(multiboot_info_t* boot_info) {
    if (boot_info == NULL) {
    } else {
        eduos_kernel_init();
    }

    vga_puts("aaa\n");

    regs16_t regs;
    int y;

    // switch to 320x200x256 graphics mode
    regs.ax = 0x0013;
    int32(0x10, &regs);

    // full screen with blue color (1)
    memset((char*)0xA0000, 1, (320 * 200));

    // draw horizontal line from 100,80 to 100,240 in multiple colors
    for (y = 0; y < 200; y++) memset((char*)0xA0000 + (y * 320 + 80), y, 160);
}