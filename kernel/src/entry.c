#include <serial.h>
#include <kprint.h>
#include <memory.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/exception.h>
#include <mem/page.h>

void _start() {
    init_serial();
    init_mem();
    init_GDT();
    init_IDT();
    init_exceptions();
    init_paging();
    kernel_switch_vtable();
    kprint("Hey. We switched!\n");
    for (;;);
}
