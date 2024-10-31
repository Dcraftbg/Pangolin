#pragma once
#include <mem/plist.h>
#include <gdt.h>

typedef struct {
    PList     plist;
    uintptr_t hhdm;
    GDTR      gdtr;
    uint64_t  GDT[5];
} Kernel;

extern Kernel kernel;
