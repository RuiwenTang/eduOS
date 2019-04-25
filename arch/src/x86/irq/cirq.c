#include <asm/irq.h>
#include <asm/vga.h>

int isr_handler(registers_t* regs) {
    char str[] = "recived interrupt:";
    char int_no = '0' + regs->int_no;
    vga_puts_color(str, BLACK | GREEN);
    vga_putchar('\n');
    vga_putchar_color(int_no, BLACK | GREEN);

    return 0;
}