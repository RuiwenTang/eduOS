#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief init arch struct
 * 1. gdt_setup()
 * 2. idt_setup()
 * 3. vga_init()
 */
void arch_init();

void arch_registe_syscall(void* call_handler);

#ifdef __cplusplus
}
#endif