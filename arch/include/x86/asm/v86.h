#ifndef __ARCH_V86_H__
#define __ARCH_V86_H__

#ifdef __cplusplus
extern "C" {
#endif

// define our structure
typedef struct __attribute__((packed)) {
    unsigned short di, si, bp, sp, bx, dx, cx, ax;
    unsigned short gs, fs, es, ds, eflags;
} regs16_t;

// tell compiler our int32 function is external
extern void int32(unsigned char intnum, regs16_t* regs);

#ifdef __cplusplus
}
#endif

#endif  // __ARCH_V86_H__