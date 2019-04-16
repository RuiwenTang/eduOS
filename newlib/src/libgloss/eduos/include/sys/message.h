#ifndef RPC_MESSAGE_H
#define RPC_MESSAGE_H
#include <stddef.h>
#include <stdint.h>

struct mess1 {
	int m1i1;
	int m1i2;
	int m1i3;
	int m1i4;
};
struct mess2 {
	void* m2p1;
	void* m2p2;
	void* m2p3;
	void* m2p4;
};
struct mess3 {
	int	m3i1;
	int	m3i2;
	int	m3i3;
	int	m3i4;
	uint64_t m3l1;
	uint64_t m3l2;
	void*	m3p1;
	void*	m3p2;
};

struct message {
    uint32_t source;
    uint32_t type;
    union {
        struct mess1 m1;
        struct mess2 m2;
        struct mess3 m3;
    } u;
};

typedef struct message MESSAGE;

#define _STR(token)             #token
#define _SYSCALLSTR(x)          "int $" _STR(x) " "
#define INT_SYSCALL		0x80

/** @brief the syscall function which issues an interrupt to the kernel
 *
 * It's supposed to be used by the macros defined in this file as the could would read
 * cleaner then.
 *
 * @param nr System call number
 * @param arg0 Argument 0
 * @param arg1 Argument 1
 * @param arg2 Argument 2
 * @param arg3 Argument 3
 * @param arg4 Argument 4
 * @return The return value of the system call
 */
#ifdef CONFIG_X86_32
inline static long
syscall(int nr, unsigned long arg0, unsigned long arg1, unsigned long arg2,
	unsigned long arg3, unsigned long arg4)
{
	long res;

	asm volatile (_SYSCALLSTR(INT_SYSCALL)
			: "=a" (res)
			: "0" (nr), "b" (arg0), "c" (arg1), "d" (arg2), "S" (arg3), "D" (arg4)
			: "memory", "cc");

	return res;
}
#else
inline static long
syscall(int nr, unsigned long arg0, unsigned long arg1, unsigned long arg2,
	unsigned long arg3, unsigned long arg4)
{
	long res;

	asm volatile ("mov %5, %%r8; mov %6, %%r9; syscall"
			: "=a" (res)
			: "D" (nr), "S" (arg0), "d" (arg1), "c" (arg2), "m" (arg3), "m" (arg4)
			: "memory", "cc", "%r8", "%r9");

	return res;
}
#endif

int msg_send(uint32_t target, MESSAGE* msg) {
    return syscall(22, target, (uint32_t) msg, 0, 0, 0);
}

int msg_recv(uint32_t source, MESSAGE* msg) {
	return syscall(21, source, (uint32_t) msg, 0, 0, 0);
}

#endif // RPC_MESSAGE_H