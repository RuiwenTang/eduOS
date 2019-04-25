
#include <asm/gdt.h>
#include <asm/stddef.h>
#include <asm/string.h>

static gdt_entry_t k_gdts[GDT_NUM];
static gdt_ptr_t gp;

extern void gdt_flush(gdt_ptr_t* gdt_ptr);

void gdt_setup() {
    memset(k_gdts, 0, sizeof(gdt_entry_t) * GDT_NUM);
    memset(&gp, 0, sizeof(gdt_ptr_t));

    uint32_t gran_cs, gran_ds, limit;
    uint32_t index = 0;

    gran_cs = gran_ds = GDT_FLAG_32_BIT | GDT_FLAG_4K_GRAN;
    limit = 0xffffffff;

    gp.base = (uint32_t)&k_gdts;
    gp.limit = sizeof(gdt_entry_t) * GDT_NUM - 1;

    // first gdt always zero
    gdt_set_gate(index++, 0, 0, 0, 0);

    /**
     * Code segment,
     * in 32 bit kernel, it is map 0 - 4GB memory address
     */
    gdt_set_gate(index++, 0, limit,
                 GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG |
                         GDT_FLAG_PRESENT,
                 gran_cs);

    /*
     * The third entry is our Data Segment. It's EXACTLY the
     * same as our code segment, but the descriptor type in
     * this entry's access byte says it's a Data Segment
     */
    gdt_set_gate(index++, 0, limit,
                 GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG |
                         GDT_FLAG_PRESENT,
                 gran_ds);

    gdt_flush(&gp);
}

void gdt_set_gate(uint32_t index, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran) {
    if (index >= GDT_NUM) {
        return;
    }

    /**
     * gdt base property
     */
    k_gdts[index].base_low = (base & 0xffff);
    k_gdts[index].base_middle = (base >> 16) & 0xff;
    k_gdts[index].base_high = (base >> 24) & 0xff;

    /**
     * gdt limits
     */
    k_gdts[index].limit_low = (limit & 0xffff);
    k_gdts[index].granularity = (limit >> 16) & 0xf;

    /**
     * flags and access granularity
     */
    k_gdts[index].granularity |= (gran & 0xf0);
    k_gdts[index].access = access;
}