#include <serial.h>
#include <kprint.h>
#include <memory.h>
#include <gdt.h>
#include <idt.h>

void _start() {
    init_serial();
    init_mem();
    init_GDT();
    init_IDT();
    write_serial("And we have liftoff!\nTrying to call interrupt...\n");
    asm volatile("int $0x80");
    for (;;);
}
