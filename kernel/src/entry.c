#include <pit.h>
#include <pic.h>
#include <cpu.h>
#include <version.h>
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
#include <string.h>

void cat(const char* path) {
    status_t e;
    char buf[128]={0};
    Inode* file;
    if((e=vfs_open_abs(path, &file)) < 0) {
        kprint("Failed to open file `%s`: %d\n", path, (int)e);
        return;
    }
    off_t offset=0;
    kprint("cat %s\n", path);
    for(;;) {
        memset(buf, 0, sizeof(buf));
        if((e=inode_read(file, buf, offset, sizeof(buf)-1)) < 0) {
            if(e == -REACHED_EOF) break;
            kprint("Failed to read file `%s`: %d\n", path, (int)e);
            idrop(file);
            return;
        }
        offset+=e;
        kprint("%s", buf);
    }
    idrop(file);
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
            kprint("Failed to schedule get_dir_entries: %d\n", (int)e);
            idrop(dir);
            return;
        }
        while((e=future.complete(&future)) == (-PENDING));
        if(e < 0) {
            if(e==-REACHED_EOF) break;
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
void print_version() {
    kprintln("This copy of Pangolin is built from commit " COMMIT " at " __TIME__ ", " __DATE__);
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
    init_vfs();
    init_scheduler();
    unpack_ustar();
    init_pic();
    init_pit();
    print_version();
    HALT_DEVICE();
}
