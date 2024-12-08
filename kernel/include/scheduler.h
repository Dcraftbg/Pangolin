#pragma once
#include <mem/slab.h>
#include <stdint.h>
#include <list.h>

typedef uint64_t task_id_t;

typedef struct {
    struct list list;
    task_id_t tid;
    /* TODO:
     * More fields will need to be added such as pml4 address etc.
     * While the core scheduler is being developed, that's not really needed, but it'll definitely
     * be required soon enough.
     * When we get around to doing SMP, there will need to be a new "Process" structure. This is not done yet.
     */
} Task;

typedef struct {
    struct list tasklist;
    // TODO: Add another `struct list` with a list of all the scheduler queues. This will be used when we do SMP.
    // This is also why I named the above element `tasklist` instead of just `list`.
    Task *current_task;
    Cache *cache;
    task_id_t tid_upto;
} SchedulerQueue;

void init_scheduler();
Task *task_add();
Task *task_select();
