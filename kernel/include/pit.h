#pragma once
#include <pic.h>

void init_pit();

static void unlock_pit() {
    unmask_irq(0);
}

static void lock_pit() {
    mask_irq(0);
}
