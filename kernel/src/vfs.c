#include <vfs.h>
#include <kprint.h>
#include <kernel.h>
Cache* inode_cache=NULL;

#include <fs/tmpfs/tmpfs.h>
static FileSystem* get_rootfs() {
    return &tmp_fs;
}

status_t parse_abs(const char* path, Path* result) {
    if(path[0] != '/') return -INVALID_PATH;
    path++;
    *result = path_abs(path);
    return 0;
}
static const char* path_eat(const char* path) {
    while(path[0]) {
        if(*path++ == '/')
            return path;
    }
    return NULL;
}
status_t init_vfs() {
    if(!(inode_cache=init_slab_cache(sizeof(Inode), "Inode"))) {
        kprint("ERROR: Failed to create inode cache\n");
        return -NOT_ENOUGH_MEMORY;
    }
    FileSystem* rootfs = get_rootfs();
    status_t e;
    if((e=rootfs->init(rootfs)) < 0) {
        // TODO: string error reporting
        kprint("ERROR: Failed to initialise rootfs: %d\n", (int)e);
        return e;
    }
    if((e=rootfs->mount(rootfs, &kernel.root_superblock, NULL)) < 0) {
        // TODO: string error reporting
        kprint("ERROR: Failed to mount rootfs: %d\n", (int)e);
        return e;
    }
    kprint("SUCCESS: Initialised rootfs\n");
    return 0;
}
