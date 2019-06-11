/**
 * @author Stefan Lankes
 * @file arch/x86/include/asm/irq.h
 * @brief Functions related to IRQs
 *
 * This file contains functions and a pointer type related to interrupt
 * requests.
 */

#ifndef __ARCH_IRQ_H__
#define __ARCH_IRQ_H__

#include <asm/idt.h>
#include <eduos/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * I/O base of 8259 PIC Master
 */
#define PIC1 0x20
/**
 * I/O base of 8259 PIC Slaver
 */
#define PIC2 0xA0

#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define ICW1_ICW4 0x01      /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

#define PIC1_OFFSET 0x20
#define PIC2_OFFSET 0x28

#define PIC_CMD_EOI 0x20

/** @brief Pointer-type to IRQ-handling functions
 *
 * Whenever you write a IRQ-handling function it has to match this signature.
 */
typedef void (*irq_handler_t)(regs*);

/** @brief Install a custom IRQ handler for a given IRQ
 *
 * @param irq The desired irq
 * @param handler The handler to install
 */
void irq_install_handler(unsigned int irq, irq_handler_t handler);

/** @brief Clear the handler for a given IRQ
 *
 * @param irq The handler's IRQ
 */
void irq_uninstall_handler(unsigned int irq);

/** @brief Procedure to initialize IRQ
 *
 * This procedure is just a small collection of calls:
 * - idt_install();
 * - isrs_install();
 * - irq_install();
 *
 * @return Just returns 0 in any case
 */
int irq_init(void);

#define IRQ_START                    \
    asm volatile("add $0x1c, %esp"); \
    asm volatile("pusha");

#define IRQ_END asm volatile("popa");

void pic_send_eoi(uint8_t irq);

/**
 *
 */
void send_eoi(uint8_t irq);

#ifdef __cplusplus
}
#endif

#endif