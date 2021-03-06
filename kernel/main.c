/*
 * Copyright (c) 2010, Stefan Lankes, RWTH Aachen University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the University nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <eduos/stddef.h>
#include <eduos/stdio.h>
#include <eduos/string.h>
#include <eduos/time.h>
#include <eduos/tasks.h>
#include <eduos/processor.h>
#include <eduos/tasks.h>
#include <eduos/syscall.h>
#include <eduos/memory.h>
#include <eduos/vma.h>
#include <eduos/fs.h>
#include <eduos/message.h>
#include <eduos/device.h>

#include <asm/irq.h>
#include <asm/ide.h>
#include <asm/atomic.h>
#include <asm/page.h>
#include <asm/uart.h>

/*
 * Note that linker symbols are not variables, they have no memory allocated for
 * maintaining a value, rather their address is their value.
 */
extern const void kernel_start;
extern const void kernel_end;
extern const void bss_start;
extern const void bss_end;
extern char __BUILD_DATE;
extern char __BUILD_TIME;

/* Page frame counters */
extern atomic_int32_t total_pages;
extern atomic_int32_t total_allocated_pages;
extern atomic_int32_t total_available_pages;

#if 0
// Demo of a user-level task
static void NORETURN userfoo(void* arg)
{
	char str[] = "hello from userfoo\n";

	SYSCALL3(__NR_write, 0, str, 20);
	SYSCALL1(__NR_exit, 0);

	while(1) ;
}

static char ustack[KERNEL_STACK_SIZE]  __attribute__ ((aligned (PAGE_SIZE)));

static int wrapper(void* arg)
{
	size_t* stack = (size_t*) (ustack+KERNEL_STACK_SIZE-16);

	memset(ustack, 0xCD, KERNEL_STACK_SIZE);
	*stack-- = (size_t) arg;
	*stack = (size_t) NULL; // put exit function as caller on the stack

#if 0
	// this triggers a page fault because a user task is not able to access the kernel space
	return jump_to_user_code((size_t) userfoo, (size_t) stack);
#else
	// dirty hack, map userfoo to the user space
	size_t phys = virt_to_phys(((size_t) userfoo) & PAGE_MASK);
	size_t vuserfoo = KERNEL_SPACE+PAGE_SIZE;
	page_map(vuserfoo, phys, 2, PG_PRESENT | PG_USER);
	vuserfoo += (size_t)userfoo & (PAGE_SIZE-1);

	// dirty hack, map ustack to the user space
	phys = virt_to_phys((size_t) ustack);
	size_t vstack = 3*KERNEL_SPACE;
	page_map(vstack, phys, KERNEL_STACK_SIZE >> PAGE_BITS, PG_PRESENT | PG_RW | PG_USER);
	vstack = (vstack + KERNEL_STACK_SIZE - 16);

	return jump_to_user_code(vuserfoo, vstack);
#endif
}
#endif

tid_t ktask1_id = 0;

static int ktask1(void* arg) {

	kprintf("begin ktask1 with arg = %s\n", arg);

	MESSAGE msg;
	memset(&msg, 0, sizeof(MESSAGE));
	msg.type = 112;
	kprintf("before ktask1 msg send\n");
	int ret = msg_send(1, &msg);
	kprintf("restart ktask1 with ret = %d and return \n", ret);
	ret = msg_recv(1, &msg);
	kprintf("rece msg from 1 with msg = %d | with type = %d\n", msg.RETVAL, msg.type);

	kprintf("end with task1\n");
	return 1;
}

static int foo(void* arg)
{
	int i;

	for(i=0; i<2; i++) {
		kprintf("hello from %s\n", (char*) arg);
	}
	MESSAGE msg;
	memset(&msg, 0, sizeof(MESSAGE));
	kprintf("before foo receive msg\n");
	msg.source = 0x1234;
	int ret = msg_recv(MSG_TARGET_ANY, &msg);
	kprintf("foo receive a message ret = %d | from src = %d | with type = %d \n", ret, msg.source, msg.type);
	msg.RETVAL = 33;
	msg.type = 1111;
	ret = msg_send(msg.source, &msg);
	kprintf("send foo finish to target ret = %d\n", ret);

	return 0;
}

static int eduos_init(void)
{
	// initialize .bss section
	memset((void*)&bss_start, 0x00, ((size_t) &bss_end - (size_t) &bss_start));

	koutput_init();
	system_init();
	irq_init();
	timer_init();
	multitasking_init();
	memory_init();
	device_init();
	ide_init();
#ifdef CONFIG_UART
	uart_init();
#endif
	initrd_init();
	fat_init();

	return 0;
}

extern int back_to_rmode();

int main(const char* real_code, uint32_t real_code_length)
{
	char* argv1[] = {"/bin/bar", NULL};
	char* argv2[] = {"/bin/hellocpp", NULL};

	eduos_init();
	system_calibration(); // enables also interrupts

	// kprintf("This is eduOS %s Build %u, %u\n", EDUOS_VERSION, &__BUILD_DATE, &__BUILD_TIME);
	// kprintf("Kernel starts at %p and ends at %p\n", &kernel_start, &kernel_end);
	// kprintf("Processor frequency: %u MHz\n", get_cpu_frequency());
	// kprintf("Total memory: %lu KiB\n", atomic_int32_read(&total_pages) * PAGE_SIZE / 1024);
	// kprintf("Current allocated memory: %lu KiB\n", atomic_int32_read(&total_allocated_pages) * PAGE_SIZE / 1024);
	// kprintf("Current available memory: %lu KiB\n", atomic_int32_read(&total_available_pages) * PAGE_SIZE / 1024);

	//vma_dump();

	// create_kernel_task(NULL, foo, "foo", NORMAL_PRIO);
	
	// create_kernel_task(&ktask1_id, ktask1, "task1", LOW_PRIO);
	// create_user_task(NULL, "/bin/hellocpp", argv1);
	create_user_task(NULL, "/bin/filemanager", argv2);
	// create_user_task(NULL, "/bin/bar", argv2);
	// kprintf("Real Code Addr = %x  | length = %d\n", (uint32_t)real_code, real_code_length);
	memcpy((void*)0x7c00, real_code, real_code_length);

	// int ret = back_to_rmode();

	// kprintf("Back from real mode ret = %d\n", ret);
#if 0
	kputs("Filesystem:\n");
	list_fs(fs_root, 1);
#endif

	// x64: wrapper maps function to user space to start a user-space task
	//create_kernel_task(NULL, wrapper, "userfoo", NORMAL_PRIO);

	while(1) { 
		HALT;
	}

	return 0;
}
