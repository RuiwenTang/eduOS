#include <asm/gdt.h>
#include <asm/idt.h>
#include <eduos/stddef.h>
#include <eduos/string.h>

#define IDT_NUM 256

idt_entry kernel_idts[IDT_NUM];

idt_ptr kernel_idt_ptr;

/* These are function prototypes for all of the exception
 *  handlers: The first 32 entries in the IDT are reserved
 *  by Intel, and are designed to service exceptions! */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void idt_install() {
    kernel_idt_ptr.limit = (sizeof(idt_entry) * IDT_NUM) - 1;
    kernel_idt_ptr.base = (unsigned int)(&kernel_idts);

    memset(&kernel_idts, 0, sizeof(idt_entry) * IDT_NUM);

    idt_set_gate(0, (size_t)isr0, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(1, (size_t)isr1, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(2, (size_t)isr2, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(3, (size_t)isr3, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(4, (size_t)isr4, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(5, (size_t)isr5, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(6, (size_t)isr6, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(7, (size_t)isr7, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(8, (size_t)isr8, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(9, (size_t)isr9, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(10, (size_t)isr10, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(11, (size_t)isr11, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(12, (size_t)isr12, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(13, (size_t)isr13, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(14, (size_t)isr14, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(15, (size_t)isr15, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(16, (size_t)isr16, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(17, (size_t)isr17, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(18, (size_t)isr18, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(19, (size_t)isr19, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(20, (size_t)isr20, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(21, (size_t)isr21, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(22, (size_t)isr22, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(23, (size_t)isr23, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(24, (size_t)isr24, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(25, (size_t)isr25, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(26, (size_t)isr26, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(27, (size_t)isr27, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(28, (size_t)isr28, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(29, (size_t)isr29, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(30, (size_t)isr30, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);
    idt_set_gate(31, (size_t)isr31, KERNEL_CODE_SELECTOR,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32BIT |
                         IDT_FLAG_INTTRAP);

    idt_flush(&kernel_idt_ptr);
}

/** @brief Configures and returns a IDT entry with chosen attributes
 *
 * Just feed this function with base, selector and the flags
 * you have seen in idt.h
 *
 * @return a preconfigured idt descriptor
 */
static void configure_idt_entry(idt_entry* dest_entry, size_t base,
                                unsigned short sel, unsigned char flags);

/*
 * Use this function to set an entry in the IDT. Alot simpler
 * than twiddling with the GDT ;)
 */
void idt_set_gate(unsigned char num, size_t base, unsigned short sel,
                  unsigned char flags) {
    configure_idt_entry(&kernel_idts[num], base, sel, flags);
}

void configure_idt_entry(idt_entry* dest_entry, size_t base, unsigned short sel,
                         unsigned char flags) {
    /* The interrupt routine's base address */
    dest_entry->base_lo = (base & 0xFFFF);
    dest_entry->base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
     *  is set here, along with any access flags */
    dest_entry->sel = sel;
    dest_entry->always0 = 0;
    dest_entry->flags = flags;
}