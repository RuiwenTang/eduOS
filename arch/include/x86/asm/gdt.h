#pragma once

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GDT_NUM 10

/// This segment is a data segment
#define GDT_FLAG_DATASEG 0x02
/// This segment is a code segment
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS 0x09
#define GDT_FLAG_TSS_BUSY 0x02

#define GDT_FLAG_SEGMENT 0x10
/// Privilege level: Ring 0
#define GDT_FLAG_RING0 0x00
/// Privilege level: Ring 1
#define GDT_FLAG_RING1 0x20
/// Privilege level: Ring 2
#define GDT_FLAG_RING2 0x40
/// Privilege level: Ring 3
#define GDT_FLAG_RING3 0x60
/// Segment is present
#define GDT_FLAG_PRESENT 0x80
/// Segment was accessed
#define GDT_FLAG_ACCESSED 0x01
/**
 * @brief Granularity of segment limit
 * - set: segment limit unit is 4 KB (page size)
 * - not set: unit is bytes
 */
#define GDT_FLAG_4K_GRAN 0x80
/**
 * @brief Default operand size
 * - set: 32 bit
 * - not set: 16 bit
 */
#define GDT_FLAG_16_BIT 0x00
#define GDT_FLAG_32_BIT 0x40
#define GDT_FLAG_64_BIT 0x20

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct {
    uint16_t limit_low;   // The lower 16 bits of the limit.
    uint16_t base_low;    // The lower 16 bits of the base.
    uint8_t base_middle;  // The next 8 bits of the base.
    /**
     * 7 6 5 4  3~~~~~~~~~~~~~~0
     * G D 0 A  SEG length 19:16
     */
    uint8_t access;  // Access flags, determine what ring this segment can be
                     // used in.
    uint8_t granularity;
    uint8_t base_high;  // The last 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct {
    uint16_t limit;  // The upper 16 bits of all selector limits.
    uint32_t base;   // The address of the first gdt_entry_t struct.
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

/**
 * @brief set up GDT
 *
 */
void gdt_setup();

/**
 * @brief  init specify GDT property
 *
 * @param index         GDT index
 * @param base          GDT addr base
 * @param limit         GDT memory length
 * @param access        GDT access flags
 * @param gran          GDT granularity flags
 */
void gdt_set_gate(uint32_t index, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran);

#ifdef __cplusplus
}
#endif
