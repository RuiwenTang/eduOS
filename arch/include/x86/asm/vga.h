#pragma once

#include <asm/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum vga_color {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE
};

typedef enum vga_color vga_color_t;

/** @brief Initialize VGA output and clear the screen */
void vga_init(void);

/** @brief Simple string output on screen.
 *
 * If you want a new line you will have to "\\n".
 *
 * @return Length of output in bytes
 */
int vga_puts(const char* text);

int vga_puts_color(const char* text, uint8_t color);

/** @brief Simple character output on screen.
 *
 * @return The original input character casted to int
 */
int vga_putchar(unsigned char c);

/**
 * @brief Simple character output on screen.
 *
 * @param c             char to be display
 * @param color         color attrib back_color | font_color
 * @return int          The original input character casted to int
 */
int vga_putchar_color(unsigned char c, uint8_t color);

/** @brief Clear the screen */
void vga_cls(void);

#ifdef __cplusplus
}
#endif
