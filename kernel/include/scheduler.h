#pragma once
#include <mem/slab.h>
#include <stdint.h>
#include <list.h>

typedef uint64_t pid_t;

typedef struct {
    struct list list;
    pid_t pid;
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
    Cache *cache;
    pid_t pid_upto;
} SchedulerQueue;

void init_scheduler();
pid_t task_add();
