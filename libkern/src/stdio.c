#include <asm/string.h>
#include <asm/vga.h>
#include <eduos/stdio.h>

int kputchar(int c) {
    vga_putchar(c);
    return 1;
}

int kputs(const char* text) {
    uint32_t len = strlen(text);
    vga_puts(text);
    return len;
}