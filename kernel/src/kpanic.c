#include <kpanic.h>
#include <kprint.h>
#include <stdarg.h>
void kpanic(const char* fmt, ...) {
    va_list args;
    kprint("KERNEL PANIC:\n");
    va_start(args, fmt);
    kprint_va(fmt, args);
    va_end(args);
    kprint("\n");
    asm volatile ("cli");
    for(;;) asm volatile("hlt");
}
