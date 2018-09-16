#ifndef OS_MESSAGE_H
#define OS_MESSAGE_H
#include <eduos/stddef.h>

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

/**
* @enum msgtype
* @brief MESSAGE types
*/
enum msgtype {
	/*
	* when hard interrupt occurs, a msg (with type==HARD_INT) will
	* be sent to some tasks
	*/
	HARD_INT = 1,

	/* SYS task */
	GET_TICKS, GET_PID, GET_RTC_TIME,

	/* FS */
	OPEN, CLOSE, READ, WRITE, LSEEK, STAT, UNLINK,

	/* FS & TTY */
	SUSPEND_PROC, RESUME_PROC,

	/* MM */
	EXEC, WAIT,

	/* FS & MM */
	FORK, EXIT,

	/* TTY, SYS, FS, MM, etc */
	SYSCALL_RET,

	/* message type for drivers */
	DEV_OPEN = 1001,
	DEV_CLOSE,
	DEV_READ,
	DEV_WRITE,
	DEV_IOCTL
};

typedef struct message MESSAGE;

#define	RETVAL		u.m3.m3i1

#define MSG_TARGET_ANY 0xffffffff
#define MSG_TARGET_INTERRUPT 0xfffffffe
#define MSG_TARGET_NONE 0x0

/**
 * 
 */
int msg_send(int target, MESSAGE* msg);
int msg_recv(int src, MESSAGE* msg);
int do_msg_send(int source, int target, MESSAGE* msg);
int do_msg_recv(int srouce, int target, MESSAGE* msg);

#endif // OS_MESSAGE_H