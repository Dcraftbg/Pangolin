#pragma once
#include <io.h>

void init_pic();
void unmask_irq(int IRQ);
void mask_irq(int IRQ);

static void end_of_interrupt() {
    outb(0x20, 0x20);
}
