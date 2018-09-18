#include <eduos/message.h>
#include <eduos/string.h>
#include <eduos/syscall.h>
#include <eduos/tasks.h>
#include <eduos/tasks_types.h>
#include <eduos/stdio.h>

static int dead_block(int src, int dst) {
    task_t* dest = get_task(dst);

    while(dest) {
        if (dest->rpc_status == TASK_MSG_SENDING) {
            if (dest->p_sendto == src) {
                return 1;
            }
            dest = get_task(dest->p_sendto);
        } else {
            break;
        }
    }

    return 0;
}

int msg_send(int target, MESSAGE* msg) {
    return syscall(__NR_send, target, (uint32_t) msg, 0, 0, 0);
}


int msg_recv(int source, MESSAGE* msg) {
    return syscall(__NR_recv, source, (uint32_t) msg, 0, 0, 0);
}


int do_msg_send(int source, int target, MESSAGE* msg) {
    msg->source = source;
    if (dead_block(source, target)) {
        // message send deadblock
        kprintf("do_msg_send meet deadblock !!!!");
        return 1;
    } 
    task_t* s_task = get_task(source);
    task_t* t_task = get_task(target);

    if (t_task == 0 || s_task == 0) {
        return -1;
    }
    

    if (t_task->rpc_status == TASK_MSG_RECEVING
        && (t_task->p_recvfrom == source || t_task->p_recvfrom == MSG_TARGET_ANY)) {
            // target is waiting for receive message
            void* src = msg;
            void* dst = virt_to_phys(t_task->p_msg);
            ((MESSAGE*) dst)->source = source;
            
            memcpy(dst, src, sizeof(MESSAGE));
            t_task->p_msg = 0;
            t_task->rpc_status = 0;
            t_task->p_recvfrom = MSG_TARGET_NONE;
            wakeup_task(t_task->id);
            reschedule();
    } else {
        // target is not waiting message
        s_task->rpc_status = TASK_MSG_SENDING;
        s_task->p_sendto = target;
        s_task->p_msg = msg;
        msg->source = source;

        task_t* p = t_task;
        if (p->sending_queue) {
            p = p->sending_queue;
            while(p->next_sending) {
                p = p->next_sending;
            }
            p->next_sending = s_task;
        } else {
            p->sending_queue = s_task;
        }
        s_task->next_sending = 0;
        // block sender
        block_task(s_task);
        reschedule();
    }

    // kprintf("do_msg_send source = %d\n", source);
    // kprintf("msg srouce = %d\n", msg->source);
    // kprintf("msg type = %d\n", msg->type);

    return 0;
}

int do_msg_recv(int source, int target, MESSAGE* msg) {
    msg->source = source;
    task_t* target_task = get_task(target);
    task_t* prev = 0;
    task_t* p_from = 0;

    int copyok = 0;

    if (source == target) {
        return -1;
    }

    if (target_task->has_int_message
        && (source == MSG_TARGET_ANY) || (source == MSG_TARGET_INTERRUPT)
    ) {
        MESSAGE rece_msg;
        memset(&rece_msg, 0, sizeof(MESSAGE));
        rece_msg.source = MSG_TARGET_INTERRUPT;
        rece_msg.type = HARD_INT;

        memcpy(msg, &rece_msg, sizeof(MESSAGE));

        target_task->has_int_message = 0;
        target_task->rpc_status = 0;
        target_task->p_msg = 0;
        target_task->p_sendto = 0;
        return 0;
    }

    if (source == MSG_TARGET_ANY) {
        if (target_task->sending_queue) {
            p_from = target_task->sending_queue;

            copyok = 1;
        }
    } else {
        p_from = get_task(source);
        if (p_from) {
            if (p_from->rpc_status == TASK_MSG_SENDING && p_from->p_sendto == target) {
                copyok = 1;

                task_t* p = target_task->sending_queue;

                while(p) {
                    if (p->id == source) {
                        break;
                    }
                    prev = p;
                    p = p->next_sending;
                }
            }
        } else {
            return -1;
        }
    }

    if (copyok) {
        if (p_from == target_task->sending_queue) {
            target_task->sending_queue = p_from->next_sending;
            p_from->next_sending = 0;
        } else {
            prev->next_sending = p_from->next_sending;
            p_from->next_sending = 0;
        }

        void* p_src = virt_to_phys(p_from->p_msg);
        void* p_dst = msg;
        
        memcpy(p_dst, p_src, sizeof(MESSAGE));
        ((MESSAGE*)p_dst)->source = p_from->id;
        p_from->p_msg = 0;
        p_from->p_sendto = 0;
        p_from->rpc_status = 0;
        wakeup_task(p_from->id);
    } else {
        // no body is sending message, block current task
        target_task->rpc_status = TASK_MSG_RECEVING;
        target_task->p_recvfrom = source;
        target_task->p_msg = msg;
        block_task(target_task);
        reschedule();
    }

    return 0;
}