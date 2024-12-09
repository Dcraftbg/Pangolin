#include <scheduler.h>
#include <kprint.h>
#include <list.h>
#include <kernel.h>
#include <mem/slab.h>

void init_scheduler() {
    list_init(&kernel.scheduler.tasklist);
    kernel.scheduler.cache = init_slab_cache(sizeof(Task), "Scheduler Queue");
    kprint("Initiated scheduler.\n");
}

// TODO: More arguments will ofc need to be added here as the fields for Task increases.
pid_t task_add() {
    Task *new_task = slab_alloc(kernel.scheduler.cache);
    new_task->pid = kernel.scheduler.pid_upto++;
    list_insert(&new_task->list, &kernel.scheduler.tasklist);
    return new_task->pid;
}
