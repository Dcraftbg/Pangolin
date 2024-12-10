#pragma once
#include <vfs.h>

static status_t write_exact(Inode* file, const void* data, size_t size) {
    status_t e;
    off_t off=0;
    while(size) {
        if((e=inode_write(file, data, off, size)) < 0) return e;
        if(e == 0) return -REACHED_EOF;
        size -= e;
        off  += e;
        data += e;
    }
    return size;
}
