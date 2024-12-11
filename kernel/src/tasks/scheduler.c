#include <string.h>
#include <scheduler.h>
#include <kprint.h>
#include <list.h>
#include <kernel.h>
#include <mem/slab.h>

void init_scheduler() {
    list_init(&kernel.scheduler.tasklist);
    kernel.scheduler.cache = init_slab_cache(sizeof(Task), "Scheduler Queue");
    kernel.scheduler.current_task = (Task*) &kernel.scheduler.tasklist;
    kprint("Initiated scheduler.\n");
}

// TODO: More arguments will ofc need to be added here as the fields for Task increases.
Task *task_add(uint64_t *pml4, void *entry, Task *parent, task_flags_t flags) {
    Task *new_task   = slab_alloc(kernel.scheduler.cache);
    new_task->tid    = kernel.scheduler.tid_upto++;
    new_task->entry  = entry;
    new_task->parent = parent;
    new_task->flags  = flags;
    new_task->pml4   = pml4;
    memset(new_task->resources, 0, sizeof(new_task->resources));
    list_insert(&new_task->list, &kernel.scheduler.tasklist);
    return new_task;
}

Task *task_select() {
    kernel.scheduler.current_task = (Task*) kernel.scheduler.current_task->list.next;
    if (&kernel.scheduler.current_task->list == &kernel.scheduler.tasklist)
        kernel.scheduler.current_task = (Task*) kernel.scheduler.current_task->list.next;
    return (Task*) kernel.scheduler.current_task;
}
