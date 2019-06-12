#include <asm/idt.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/vga.h>
#include <eduos/stddef.h>

/* This will keep track of how many ticks that the system
 *  has been running for */
uint32_t timer_ticks = 0;

void timer_phase(int hz) {
    int divisor = 1193180 / hz;     /* Calculate our divisor */
    outportb(0x43, 0x36);           /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF); /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);   /* Set high byte of divisor */
}

/* Handles the timer. In this case, it's very simple: We
 *  increment the 'timer_ticks' variable every time the
 *  timer fires. By default, the timer fires 18.222 times
 *  per second. Why 18.222Hz? Some engineer at IBM must've
 *  been smoking something funky */
void timer_handler(regs* r) {
    UNUSED(r);
    /* Increment our 'tick count' */
    timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
     *  display a message on the screen */
    if (timer_ticks % 18 == 0) {
    }
}

/* Sets up the system clock by installing the timer handler
 *  into IRQ0 */
void timer_install() {
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}