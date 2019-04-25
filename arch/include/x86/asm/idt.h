#pragma once

#include <asm/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This bit shall be set to 0 if the IDT slot is empty
#define IDT_FLAG_PRESENT 0x80
/// Interrupt can be called from within RING0
#define IDT_FLAG_RING0 0x00
/// Interrupt can be called from within RING1 and lower
#define IDT_FLAG_RING1 0x20
/// Interrupt can be called from within RING2 and lower
#define IDT_FLAG_RING2 0x40
/// Interrupt can be called from within RING3 and lower
#define IDT_FLAG_RING3 0x60
/// Size of gate is 16 bit
#define IDT_FLAG_16BIT 0x00
/// Size of gate is 32 bit
#define IDT_FLAG_32BIT 0x08
/// The entry describes an interrupt gate
#define IDT_FLAG_INTTRAP 0x06
/// The entry describes a trap gate
#define IDT_FLAG_TRAPGATE 0x07
/// The entry describes a task gate
#define IDT_FLAG_TASKGATE 0x05

// A struct describing an interrupt gate.
struct idt_entry_struct {
    uint16_t base_lo;  // The lower 16 bits of the address to jump to when this
                       // interrupt fires.
    uint16_t sel;      // Kernel segment selector.
    uint8_t always0;   // This must always be zero.
    uint8_t flags;     // More flags. See documentation.
    uint16_t base_hi;  // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct {
    uint16_t limit;
    uint32_t
            base;  // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

/** @brief Installs IDT
 *
 * The installation involves the following steps:
 * - Set up the IDT pointer
 * - Set up int 0x80 for syscalls
 * - process idt_load()
 */
void idt_setup(void);

/** @brief Set an entry in the IDT
 *
 * @param num index in the IDT
 * @param base base-address of the handler function being installed
 * @param sel Segment the IDT will use
 * @param flags Flags this entry will have
 */
void idt_set_gate(unsigned char num, size_t base, unsigned short sel,
                  unsigned char flags);

#ifdef __cplusplus
}
#endif