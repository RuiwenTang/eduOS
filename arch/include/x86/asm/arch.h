#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief init arch struct
 * 1. gdt_setup()
 * 2. idt_setup()
 *
 */
void arch_init();

#ifdef __cplusplus
}
#endif