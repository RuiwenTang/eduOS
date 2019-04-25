#pragma once

#include <asm/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct registers {
    uint32_t ds;                                      // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // pushed by pusha
    uint32_t int_no, err_code;               // Interrupt number and error code
    uint32_t eipp, cs, eflags, useresp, ss;  // pushed by CPU interrupt
} registers_t;

/** @brief Disable IRQs
 *
 * This inline function just clears out the interrupt bit
 */
inline static void irq_disable(void) { asm volatile("cli" ::: "memory"); }

/** @brief Disable IRQs (nested)
 *
 * Disable IRQs when unsure if IRQs were enabled at all.\n
 * This function together with irq_nested_enable can be used
 * in situations when interrupts shouldn't be activated if they
 * were not activated before calling this function.
 *
 * @return The set of flags which have been set until now
 */
inline static uint8_t irq_nested_disable(void) {
    size_t flags;
    asm volatile("pushf; cli; pop %0" : "=r"(flags) : : "memory");
    if (flags & (1 << 9)) return 1;
    return 0;
}

/** @brief Enable IRQs */
inline static void irq_enable(void) { asm volatile("sti" ::: "memory"); }

/** @brief Enable IRQs (nested)
 *
 * If called after calling irq_nested_disable, this function will
 * not activate IRQs if they were not active before.
 *
 * @param flags Flags to set. Could be the old ones you got from
 * irq_nested_disable.
 */
inline static void irq_nested_enable(uint8_t flags) {
    if (flags) irq_enable();
}

/** @brief Determines, if the interrupt flags (IF) is ser
 *
 * @return
 * - 1 interrupt flag is set
 * - 0 interrupt flag is cleared
 */
inline static uint8_t is_irq_enabled(void) {
    size_t flags;
    asm volatile("pushf; pop %0" : "=r"(flags) : : "memory");
    if (flags & (1 << 9)) return 1;
    return 0;
}

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

#define MAX_HANDLERS 256

typedef void (*irq_handler_t)(void*);

void irq_install_handler(uint32_t irq, irq_handler_t handler);
void irq_uninstall_handler(uint32_t irq);

#ifdef __cplusplus
}
#endif