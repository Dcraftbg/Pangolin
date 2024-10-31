#include <serial.h>
#include <kprint.h>
#include <memory.h>
void _start() {
    init_serial();
    init_mem();
    write_serial("And we have liftoff!\n");
    for (;;);
}
