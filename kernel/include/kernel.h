#pragma once
#include <mem/plist.h>
#include <gdt.h>
#include <idt.h>

typedef struct {
    PList     plist;
    uintptr_t hhdm;
    GDTR      gdtr;
    uint64_t  GDT[5];
    IDTR      idtr;
    IDTEntry  idt[256];
} Kernel;

extern Kernel kernel;
