#include <kprint.h>
#include <pit.h>
#include <pic.h>
#include <cpu/idt.h>

#define HERTZ_DIVIDER 1190

// TODO: Link this to the context switch - it's currently just a test interrupt
__attribute__((interrupt))
void pit_isr(void*) {
    kprint("Got PIT interrupt.\n");
    end_of_interrupt();
}

void init_pit() {
    outb(0x43, 0b110100); // set mode to rate generator, channel 0, lobyte/hibyte, binary mode
    outb(0x40, (HERTZ_DIVIDER) & 0xFF);
    outb(0x40, (HERTZ_DIVIDER >> 8) & 0xFF);
    set_IDT_entry(32, &pit_isr, 0x8F, kernel.idt);
    lock_pit();
    kprint("Initialised PIT.\n");
}
