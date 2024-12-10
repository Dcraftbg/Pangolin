#pragma once
#include <scheduler.h>
#include <mem/plist.h>
#include <mem/page.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <bootutils.h>
#include <vfs.h>

typedef struct {
    PList       plist;
    uintptr_t   hhdm;
    uint64_t *GDT;
    IDTR idtr;
    IDTEntry *idt;
    Framebuffer framebuffer;
    page_t pml4;
    uint64_t char_x;
    uint64_t char_y;
    struct list *slab_caches;
    Superblock  root_superblock;
    // TODO: This shold become a `struct list` at some point once there are multiple scheduler queues,
    // one for each processor, when we get to SMP.
    SchedulerQueue scheduler;
} Kernel;

extern Kernel kernel;
