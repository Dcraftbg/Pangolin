#include <serial.h>
#include <kprint.h>
void _start() {
    init_serial();
    write_serial("And we have liftoff!\n");
    kprint("Hello %d\n", -1234);
    for (;;);
}
