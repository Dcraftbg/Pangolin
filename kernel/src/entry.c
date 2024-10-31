#include <serial.h>
#include <kprint.h>
#include <memory.h>
#include <cpu.h>

void _start() {
    init_serial();
    init_mem();
    init_GDT();
    write_serial("And we have liftoff!\n");
    for (;;);
}
