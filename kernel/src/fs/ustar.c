#include <fs/ustar.h>
#include <kprint.h>
#include <kpanic.h>
#include <bootutils.h>
#include <vfs.h>
#include <string.h>

#define FILENAME_OFF  0
#define INDICATOR_OFF 257
#define FILESIZE_OFF  0x7C
#define TYPE_OFF      156

// TODO: Move this out to fsutils or some other module
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

// TODO: Boundary checks
// TODO: Actually copy the file contents to the files

void unpack_ustar() {
    status_t e;
    char *at = (char*) boot_get_initrd();
    while (!memcmp(at + INDICATOR_OFF, "ustar", 5)) {
        size_t size = oct2bin(at + FILESIZE_OFF, 11);
        char *filename = at + FILENAME_OFF;
        bool is_dir = (*(at + TYPE_OFF) & 0b111) == 5;
        char *label = (is_dir) ? "Directory" : "File";
        memmove(filename + 1, filename, strlen(filename));
        filename[0] = '/';
        kprint("%s found with name \"%s\", of size %zu bytes.\n", label, filename, size);
        if (is_dir) {
            filename[strlen(filename) - 1] = 0;
            if((e=vfs_mkdir_abs(filename)) < 0)
                kpanic("Failed to create directory `%s`: %d\n", filename, (int)e);
            
            at += (((size + 511) / 512) + 1) * 512;
            continue;
        }
        {
            if((e=vfs_create_abs(filename)) < 0)
                kpanic("Failed to create file `%s`: %d", filename, (int)e);
            
            Inode* file;
            if((e=vfs_open_abs(filename, &file)) < 0)
                kpanic("Failed to open file `%s`: %d", filename, (int)e);
            if((e=write_exact(file, at+512, size)) < 0) {
                idrop(file);
                kpanic("Failed to write to file `%s`: %d", filename, (int)e);
            }
            idrop(file);
        }
        at += (((size + 511) / 512) + 1) * 512;
    }
    kprint("Unpack USTAR.\n");
}
