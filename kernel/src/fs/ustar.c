#include <fsutils.h>
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

void unpack_ustar() {
    status_t e;
    char *at = (char*) boot_get_initrd();
    while (!memcmp(at + INDICATOR_OFF, "ustar", 5)) {
        size_t size = oct2bin(at + FILESIZE_OFF, 11);
        char *filename = at + FILENAME_OFF;
        bool is_dir = (*(at + TYPE_OFF) & 0b111) == 5;
        char *label = (is_dir) ? "Directory" : "File";
        size_t filename_len = strlen(filename);
        if (filename_len > 98) // not enough space to prepend `/`
            kpanic("Initial ramdisk filename is too long: not enough space to prepend \"/\".\n");
        memmove(filename + 1, filename, filename_len);
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
    kprint("Unpacked initial ramdisk onto tmpfs.\n");
}
