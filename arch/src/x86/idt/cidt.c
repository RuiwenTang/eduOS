
#include <asm/idt.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/string.h>

#define KERNEL_CODE_SELECTOR 0x8

char str1[] = "Division By Zero";
char str2[] = "Debug";
char str3[] = "Non Maskable Interrupt";
char str4[] = "Breakpoint";
char str5[] = "Into Detected Overflow";
char str6[] = "Out of Bounds";
char str7[] = "Invalid Opcode";
char str8[] = "No Coprocessor";
char str9[] = "Double Fault";
char str10[] = "Coprocessor Segment Overrun";
char str11[] = "Bad TSS";
char str12[] = "Segment Not Present";
char str13[] = "Stack Fault";
char str14[] = "General Protection Fault";
char str15[] = "Page Fault";
char str16[] = "Unknown Interrupt";
char str17[] = "Coprocessor Fault";
char str18[] = "Alignment Check";
char str19[] = "Machine Check";

/** @brief Exception messages
 *
 * This is a simple string array. It contains the message that
 * corresponds to each and every exception. We get the correct
 * message by accessing it like this:
 * exception_message[interrupt_number]
 */
static const char* exception_messages[] = {
        str1,  str2,  str3,  str4,  str5,  str6,  str7,  str8,
        str9,  str10, str11, str12, str13, str14, str15, str16,
        str17, str18, str19, 0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0};

static idt_entry_t k_idts[256];
static idt_ptr_t k_idt_ptr;

extern void idt_flush(idt_ptr_t* idt_ptr);

static void fault_handler(registers_t regs);

void idt_setup() {
    k_idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    k_idt_ptr.base = (uint32_t)&k_idts;

    memset(k_idts, 0, sizeof(idt_entry_t) * 256);

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

    idt_flush(&k_idt_ptr);
}

void idt_set_gate(unsigned char num, size_t base, unsigned short sel,
                  unsigned char flags) {
    k_idts[num].base_lo = base & 0xFFFF;
    k_idts[num].base_hi = (base >> 16) & 0xFFFF;

    k_idts[num].sel = sel;
    k_idts[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    k_idts[num].flags = flags /* | 0x60 */;
}

/*
 * All of our Exception handling Interrupt Service Routines will
 * point to this function. This will tell us what exception has
 * occured! Right now, we simply abort the current task.
 * All ISRs disable interrupts while they are being
 * serviced as a 'locking' mechanism to prevent an IRQ from
 * happening and messing up kernel data structures
 */
static void fault_handler(registers_t regs) {
    if (regs.int_no < 32) {
        // kputs(exception_messages[s->int_no]);
        // kprintf(" Exception (%d) at 0x%x:0x%x, error code 0x%x, eflags
        // 0x%x\n",
        //         s->int_no, s->cs, s->eip, s->error, s->eflags);

        outportb(0x20, 0x20);

        irq_enable();
        // abort();
        while (1) {
        }
    }
}