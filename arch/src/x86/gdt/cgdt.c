
#include <asm/gdt.h>
#include <asm/stddef.h>

static gdt_entry_t k_gdts[GDT_NUM];

void gdt_setup() {}