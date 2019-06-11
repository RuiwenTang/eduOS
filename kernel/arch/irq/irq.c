#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/vga.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void* irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(unsigned int irq, irq_handler_t handler) {
    irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(unsigned int irq) { irq_routines[irq] = 0; }

/* Each of the IRQ ISRs point to this function, rather than
 *  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
 *  to be told when you are done servicing them, so you need
 *  to send them an "End of Interrupt" command (0x20). There
 *  are two 8259 chips: The first exists at 0x20, the second
 *  exists at 0xA0. If the second controller (an IRQ from 8 to
 *  15) gets an interrupt, you need to acknowledge the
 *  interrupt at BOTH controllers, otherwise, you only send
 *  an EOI command to the first controller. If you don't send
 *  an EOI, you won't raise any more IRQs */
void irq_handler(regs* r) {
    /* This is a blank function pointer */
    void (*handler)(regs * r);

    /* Find out if we have a custom handler to run for this
     *  IRQ, and then finally, run it */
    handler = irq_routines[r->int_no - 32];
    if (handler) {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
     *  (meaning IRQ8 - 15), then we need to send an EOI to
     *  the slave controller */
    if (r->int_no >= 40) {
        outportb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
     *  interrupt controller too */
    outportb(0x20, 0x20);
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
 *  is a problem in protected mode, because IDT entry 8 is a
 *  Double Fault! Without remapping, every time IRQ0 fires,
 *  you get a Double Fault Exception, which is NOT actually
 *  what's happening. We send commands to the Programmable
 *  Interrupt Controller (PICs - also called the 8259's) in
 *  order to make IRQ0 to 15 be remapped to IDT entries 32 to
 *  47 */
void irq_remap(void) {
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

int irq_init(void) {
    irq_remap();

    idt_set_gate(32, (size_t)irq0, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(33, (size_t)irq1, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(34, (size_t)irq2, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(35, (size_t)irq3, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(36, (size_t)irq4, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(37, (size_t)irq5, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(38, (size_t)irq6, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(39, (size_t)irq7, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(40, (size_t)irq8, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(41, (size_t)irq9, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(42, (size_t)irq10, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(43, (size_t)irq11, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(44, (size_t)irq12, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(45, (size_t)irq13, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(46, (size_t)irq14, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(47, (size_t)irq15, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);

    return 0;
}
