#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EDUOS_VERSION "0.1"
#define MAX_TASKS 16
#define MAX_FNAME 128
#define TIMER_FREQ 100 /* in HZ */
#define CLOCK_TICK_RATE                                                     \
    1193182                    /* 8254 chip's internal oscillator frequency \
                                */
#define VIDEO_MEM_ADDR 0xB8000 /* the video memory address */
#define CACHE_LINE 64
#define KERNEL_STACK_SIZE (8 << 10)    /*  8 KiB */
#define DEFAULT_STACK_SIZE (16 * 1024) /* 16 KiB */
#define BITMAP_SIZE (128 << 5)         /* for 128 MiB of RAM */
#define KMSG_SIZE (8 * 1024)
#define INT_SYSCALL 0x80
#define MAILBOX_SIZE 32

#define BYTE_ORDER LITTLE_ENDIAN

/*
 * This is not IDT-flag related. It's the segment selectors for kernel code and
 * data.
 */
#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define CONFIG_VGA
#define CONFIG_PCI
//#define CONFIG_UART

// #define BUILTIN_EXPECT(exp, b)  __builtin_expect((exp), (b))
#define BUILTIN_EXPECT(exp, b) (exp)
#define NORETURN __attribute__((noreturn))
#define STDCALL __attribute__((stdcall))

#define HAVE_ARCH_MEMSET
#define HAVE_ARCH_MEMCPY
#define HAVE_ARCH_STRLEN
#define HAVE_ARCH_STRCPY
#define HAVE_ARCH_STRNCPY

#ifdef __cplusplus
}
#endif

#endif