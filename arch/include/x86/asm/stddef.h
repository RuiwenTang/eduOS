#ifndef __ARCH_STDDEF_H__
#define __ARCH_STDDEF_H__

#ifdef __cplusplus
extern "C" {
#endif


#define KERNEL_SPACE	(1UL << 30) /*  1 GiB */

/// This type is used to represent the size of an object.
typedef unsigned long size_t;
/// Pointer differences
typedef long ptrdiff_t;
/// It is similar to size_t, but must be a signed type.
typedef long ssize_t;
/// The type represents an offset and is similar to size_t, but must be a signed type.
typedef long off_t;

#ifdef __KERNEL__
typedef long long ssize_t;
typedef long long off_t;
#endif

/// Unsigned 64 bit integer
typedef unsigned long long uint64_t;
/// Signed 64 bit integer
typedef long long int64_t;
/// Unsigned 32 bit integer
typedef unsigned int uint32_t;
/// Signed 32 bit integer
typedef int int32_t;
/// Unsigned 16 bit integer
typedef unsigned short uint16_t;
/// Signed 16 bit integer
typedef short int16_t;
/// Unsigned 8 bit integer (/char)
typedef unsigned char uint8_t;
/// Signed 8 bit integer (/char)
typedef char int8_t;
/// 16 bit wide char type
typedef unsigned short wchar_t;

/// This defines what the stack looks like after the task context is saved.
struct state {
	/// ds register
	uint32_t ds;
	/// es register
	uint32_t es;
	/// EDI register
	uint32_t edi;
	/// ESI register
	uint32_t esi;
	/// EBP register
	uint32_t ebp;
	/// ESP register
	uint32_t esp;
	/// EBX register 
	uint32_t ebx;
	/// EDX register
	uint32_t edx;
	/// ECX register
	uint32_t ecx;
	/// EAX register
	uint32_t eax;		/* pushed by 'pusha' */

	/// Interrupt number
	uint32_t int_no;

	// pushed by the processor automatically
	uint32_t error;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss;
};

#ifdef __cplusplus
}
#endif

#endif