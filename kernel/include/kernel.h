#pragma once
#include <mem/plist.h>
#include <mem/page.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <bootutils.h>

typedef struct {
    PList       plist;
    uintptr_t   hhdm;
    // TODO: Remove this entirely.
    // You can just place it on the stack.
    // Its not necessary
    GDTR        gdtr;
    uint64_t    GDT[5];
    // TODO: Remove this entirely.
    // You can just place it on the stack.
    // Its not necessary
    IDTR        idtr;
    IDTEntry    idt[256] __attribute__((aligned(4096)));
    Framebuffer framebuffer;
    page_t pml4;
    uint64_t char_x;
    uint64_t char_y;
} Kernel;

extern Kernel kernel;
