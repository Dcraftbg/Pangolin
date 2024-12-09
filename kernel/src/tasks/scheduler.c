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
