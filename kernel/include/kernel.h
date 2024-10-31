#pragma once
#include <mem/plist.h>
typedef struct {
    PList plist;
    uintptr_t hhdm;
} Kernel;
extern Kernel kernel;
