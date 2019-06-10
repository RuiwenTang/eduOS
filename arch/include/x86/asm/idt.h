#ifndef _EDUOS_IDT_H_
#define _EDUOS_IDT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <eduos/stddef.h>

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

typedef struct _idt_entry {
    unsigned short base_lo;
    unsigned short sel;    /* Our kernel segment goes here! */
    unsigned char always0; /* This will ALWAYS be set to 0! */
    unsigned char flags;   /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed)) idt_entry;

typedef struct _idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_ptr;

/**
 * @brief implement in asm
 * load custom idt pointer
 * @param idt_ptr
 */
extern void idt_flush(idt_ptr*);

/**
 * @brief init system idt
 *
 */
void idt_install();

/** @brief Set an entry in the IDT
 *
 * @param num index in the IDT
 * @param base base-address of the handler function being installed
 * @param sel Segment the IDT will use
 * @param flags Flags this entry will have
 */
void idt_set_gate(unsigned char num, size_t base, unsigned short sel,
                  unsigned char flags);

typedef struct _regs {
    unsigned int gs, fs, es, ds; /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
    unsigned int int_no, err_code; /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp,
            ss; /* pushed by the processor automatically */
} regs;

#ifdef __cplusplus
}
#endif

#endif  // _EDUOS_IDT_H_