#include <eduos/tasks.h>

void set_kernel_stack(void) {}

size_t* get_current_stack(void) {
    // task_t* curr_task = current_task;

    // // use new page table
    // write_cr3(curr_task->page_map);

    // return curr_task->last_stack_pointer;
    return NULL;
}

task_t* get_current_task(void) { return NULL; }

/** @brief Aborting a task is like exiting it with result -1 */
void NORETURN abort(void) {
    // do_exit(-1);
}

void finish_task_switch(void) {}

size_t** scheduler(void) { return NULL; }

uint32_t get_highest_priority(void) { return 0; }