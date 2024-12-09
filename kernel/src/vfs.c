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
// NOTE: Maybe consider writing some helper macros for this. but idrk, I think its fine to write them out
// by hand for now
status_t schedule_write(Inode* inode, const void* data, off_t offset, size_t size, FsFuture* future) {
    if(!inode->ops->schedule_write) return -UNSUPPORTED;
    return inode->ops->schedule_write(inode, data, offset, size, future);
}
status_t schedule_read(Inode* inode, void* data      , off_t offset, size_t size, FsFuture* future) {
    if(!inode->ops->schedule_read) return -UNSUPPORTED;
    return inode->ops->schedule_read(inode, data, offset, size, future);
}
status_t create(Inode* dir, const char* name, size_t namelen) {
    if(!dir->ops->create) return -UNSUPPORTED;
    return dir->ops->create(dir, name, namelen);
}
status_t mkdir(Inode* dir, const char* name, size_t namelen) {
    if(!dir->ops->mkdir) return -UNSUPPORTED;
    return dir->ops->mkdir(dir, name, namelen);
}
status_t find(Inode* dir, const char* name, size_t namelen, DirEntry* direntry) {
    if(!dir->ops->find) return -UNSUPPORTED;
    return dir->ops->find(dir, name, namelen, direntry);
}
status_t schedule_get_dir_entries(Inode* dir, DirEntry* entries, off_t offset, size_t count, FsFuture* future) {
    if(!dir->ops->schedule_get_dir_entries) return -UNSUPPORTED;
    return dir->ops->schedule_get_dir_entries(dir, entries, offset, count, future);
}
status_t inode_cleanup(Inode* inode) {
    if(!inode->ops->cleanup) return -UNSUPPORTED;
    return inode->ops->cleanup(inode);
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
