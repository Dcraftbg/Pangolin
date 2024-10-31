#include <idt.h>
#include <kernel.h>
#include <kprint.h>

__attribute__((interrupt))
void test_interrupt(void*) {
    kprint("Oh gee golly I got an interrupt, how amazing\n");
}

void set_IDT_entry(uint32_t vector, void *isr, uint8_t flags, IDTEntry *IDT) {
    IDT[vector].offset1 = (uint64_t)isr;
    IDT[vector].offset2 = ((uint64_t)isr) >> 16;
    IDT[vector].offset3 = ((uint64_t)isr) >> 32;
    IDT[vector].flags   = flags;
    IDT[vector].segment_selector = 0x08;
}

void init_IDT() {
    set_IDT_entry(0x80, &test_interrupt, 0x8E, (IDTEntry*) &kernel.idt);
    kernel.idtr = (IDTR) {
        .size   = (sizeof(IDTEntry) * 256) - 1,
        .offset = (uint64_t) &kernel.idt
    };
    asm("lidt %0" : : "m" (kernel.idtr));
}