#pragma once

#include <asm/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Initialize VGA output and clear the screen */
void vga_init(void);

/** @brief Simple string output on screen.
 *
 * If you want a new line you will have to "\\n".
 *
 * @return Length of output in bytes
 */
int vga_puts(const char* text);

/** @brief Simple character output on screen.
 *
 * @return The original input character casted to int
 */
int vga_putchar(unsigned char c);

/** @brief Clear the screen */
void vga_cls(void);

#ifdef __cplusplus
}
#endif
