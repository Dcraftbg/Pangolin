#include <mem/slab.h>
#include <framebuffer.h>
#include <serial.h>
#include <kprint.h>
#include <memory.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/exception.h>
#include <mem/page.h>

void _start() {
    init_serial();
    init_framebuffer();
    init_mem();
    init_GDT();
    init_IDT();
    init_exceptions();
    init_paging();
    kernel_switch_vtable();
    kprint("Switched page tree.\n");
    Cache *cache = init_slab_cache(4, "Test Cache\0");
    for (size_t i = 0; i < 20; i++) {
        void *addr = slab_alloc(cache);
        kprint("Addr = %p\n", addr);
    }
    asm volatile("cli");
    for (;;);
}
