#include <fs/ustar.h>
#include <kprint.h>
#include <bootutils.h>
#include <vfs.h>
#include <string.h>

#define FILENAME_OFF  0
#define INDICATOR_OFF 257
#define FILESIZE_OFF  0x7C
#define TYPE_OFF      156

// TODO: Actually copy the file contents to the files

void unpack_ustar() {
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
            vfs_mkdir_abs(filename);
            at += (((size + 511) / 512) + 1) * 512;
            continue;
        }
        vfs_create_abs(filename);
        at += (((size + 511) / 512) + 1) * 512;
    }
    kprint("Unpack USTAR.\n");
}
