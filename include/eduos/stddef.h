#pragma once

#include <asm/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NULL 0

/// represents a task identifier
typedef unsigned int tid_t;

struct task;
/// pointer to the current (running) task
extern struct task* current_task;



#ifdef __cplusplus
}
#endif