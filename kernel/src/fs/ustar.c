#include <fs/ustar.h>
#include <kprint.h>
#include <bootutils.h>

void unpack_ustar() {
    kprint("USTAR contents: %p\n", (void*) boot_get_initrd());
    kprint("Unpack USTAR.\n");
}
