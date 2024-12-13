#include <string.h>
#include <scheduler.h>
#include <kprint.h>
#include <list.h>
#include <kernel.h>
#include <mem/slab.h>

void init_scheduler() {
    list_init(&kernel.scheduler.tasklist);
    kernel.scheduler.cache = init_slab_cache(sizeof(Task), "Scheduler Queue");
    // init the kernel task
    Task *krnl_task   = task_add();
    krnl_task->pml4   = kernel.pml4;
    krnl_task->entry  = &_start;
    krnl_task->parent = krnl_task; // The kernel task is it's own parent
    krnl_task->flags  = 0;
    memset(krnl_task->resources, 0, sizeof(krnl_task->resources));
    kernel.scheduler.current_task = krnl_task;
    kprint("Initiated scheduler.\n");
}

Task *task_add() {
    Task *new_task   = slab_alloc(kernel.scheduler.cache);
    new_task->tid    = kernel.scheduler.tid_upto++;
    memset(new_task->resources, 0, sizeof(new_task->resources));
    list_insert(&new_task->list, &kernel.scheduler.tasklist);
    return new_task;
}

Task *task_select() {
    kernel.scheduler.current_task = (Task*) kernel.scheduler.current_task->list.next;
    if (!(kernel.scheduler.current_task->flags & TASK_PRESENT) ||
        &kernel.scheduler.current_task->list == &kernel.scheduler.tasklist)
            kernel.scheduler.current_task = (Task*) kernel.scheduler.current_task->list.next;
    return (Task*) kernel.scheduler.current_task;
}
