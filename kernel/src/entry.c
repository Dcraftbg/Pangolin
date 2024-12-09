#include <mem/slab.h>
#include <scheduler.h>
#include <framebuffer.h>
#include <serial.h>
#include <kprint.h>
#include <memory.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/exception.h>
#include <mem/page.h>
#include <vfs.h>

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
    init_vfs();
    init_scheduler();
    pid_t pid;
    for (size_t i = 0; i < 10; i++) {
        pid = task_add();
        kprint("New PID = %zu\n", pid);
    }
    asm volatile("cli");
    for (;;) asm volatile("hlt");
}
