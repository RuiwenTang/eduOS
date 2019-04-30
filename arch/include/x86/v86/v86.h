#ifndef __ARCH_V86_H__
#define __ARCH_V86_H__

// define our structure
typedef struct __attribute__((packed)) {
    unsigned short di, si, bp, sp, bx, dx, cx, ax;
    unsigned short gs, fs, es, ds, eflags;
} regs16_t;

void int32(unsigned char intnum, regs16_t* regs);

// void back_to_rmode(unsigned char intnum, regs16_t* regs);

#endif