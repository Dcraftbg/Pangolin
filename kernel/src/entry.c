#include <fs/ustar.h>
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

void fs_test() {
    status_t e;
    if((e=vfs_mkdir_abs("/foo")) < 0) {
        kprint("ERROR: Failed to create /foo: %d\n", (int)e);
        return;
    }
    if((e=vfs_create_abs("/hello.txt")) < 0) {
        kprint("ERROR: Failed to create /hello.txt: %d\n", (int)e);
        return;
    }
}
void ls(const char* path) {
    status_t e;
    Inode* dir;
    if((e=vfs_open_abs(path, &dir)) < 0) {
        kprint("Failed to open directory `%s`: %d\n", path, (int)e);
        return;
    }
    off_t offset=0;
    FsFuture future;
    DirEntry entry;
    char namebuf[128];
    kprint("ls %s\n", path);
    for(;;) {
        if((e=inode_schedule_get_dir_entries(dir, &entry, offset, 1, &future)) < 0) {
            if(e==-REACHED_EOF) break;
            kprint("Failed to schedule get_dir_entries: %d\n", (int)e);
            idrop(dir);
            return;
        }
        while((e=future.complete(&future)) == (-PENDING));
        if(e < 0) {
            kprint("Failed to complete future: %d\n", (int)e);
            idrop(dir);
            return;
        }
        offset += e;
        if((e=direntry_identify(&entry, namebuf, sizeof(namebuf))) < 0) {
            kprint("Failed to identify: %d\n", (int)e);
            continue;
        }
        kprint("   %s\n", namebuf);
    }
    idrop(dir);
}
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
    unpack_ustar();
    ls("/");
    ls("/home");
    asm volatile("cli");
    for (;;) asm volatile("hlt");
}
