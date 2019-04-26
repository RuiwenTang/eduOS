#pragma once

#include <eduos/config.h>
#include <eduos/stdarg.h>
#include <eduos/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Works like the ANSI C function puts
 */
int kputs(const char*);

/**
 * Works like the ANSI C function putchar
 */
int kputchar(int);

/**
 * Works like the ANSI C function printf
 */
int kprintf(const char*, ...);

/**
 * Initialize the I/O functions
 */
int koutput_init(void);

/**
 * Works like the ANSI c function sprintf
 */
int ksprintf(char* str, const char* format, ...);

/**
 * Works like the ANSI c function sprintf
 */
int ksnprintf(char* str, size_t size, const char* format, ...);

/**
 * Scaled down version of printf(3)
 */
int kvprintf(char const* fmt, void (*func)(int, void*), void* arg, int radix,
             va_list ap);

/**
 * Add UART device to dump kernel messages
 */
int koutput_add_uart(void);

#ifdef __cplusplus
}
#endif