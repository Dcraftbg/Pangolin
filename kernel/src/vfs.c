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
status_t inode_schedule_write(Inode* inode, const void* data, off_t offset, size_t size, FsFuture* future) {
    if(!inode->ops->schedule_write) return -UNSUPPORTED;
    return inode->ops->schedule_write(inode, data, offset, size, future);
}
status_t inode_schedule_read(Inode* inode, void* data      , off_t offset, size_t size, FsFuture* future) {
    if(!inode->ops->schedule_read) return -UNSUPPORTED;
    return inode->ops->schedule_read(inode, data, offset, size, future);
}
status_t inode_create(Inode* dir, const char* name, size_t namelen) {
    if(!dir->ops->create) return -UNSUPPORTED;
    return dir->ops->create(dir, name, namelen);
}
status_t inode_mkdir(Inode* dir, const char* name, size_t namelen) {
    if(!dir->ops->mkdir) return -UNSUPPORTED;
    return dir->ops->mkdir(dir, name, namelen);
}
status_t inode_find(Inode* dir, const char* name, size_t namelen, DirEntry* direntry) {
    if(!dir->ops->find) return -UNSUPPORTED;
    return dir->ops->find(dir, name, namelen, direntry);
}
status_t inode_schedule_get_dir_entries(Inode* dir, DirEntry* entries, off_t offset, size_t count, FsFuture* future) {
    if(!dir->ops->schedule_get_dir_entries) return -UNSUPPORTED;
    return dir->ops->schedule_get_dir_entries(dir, entries, offset, count, future);
}
status_t inode_cleanup(Inode* inode) {
    if(!inode->ops->cleanup) return -UNSUPPORTED;
    return inode->ops->cleanup(inode);
}


status_t sb_unmount(Superblock* superblock) {
    if(!superblock->ops->unmount) return -UNSUPPORTED;
    return superblock->ops->unmount(superblock);
}
status_t sb_get_inode(Superblock* superblock, inodeid_t id, Inode** inode) {
    if(!superblock->ops->get_inode) return -UNSUPPORTED;
    return superblock->ops->get_inode(superblock, id, inode);
}


status_t direntry_identify(DirEntry* entry, char* name, size_t namecap) {
    if(!entry->ops->identify) return -UNSUPPORTED;
    return entry->ops->identify(entry, name, namecap);
}
status_t direntry_cleanup(DirEntry* entry) {
    if(!entry->ops->cleanup) return -UNSUPPORTED;
    return entry->ops->cleanup(entry);
}


status_t vfs_find_parent(Path* path, inodeid_t* id, Superblock** sb, const char** rest) {
    status_t e;
    const char* p = path->path;
    const char* end = path_eat(p);
    *id = path->from.inode;
    *sb = path->from.superblock;
    while((end = path_eat(p))) {
        Inode* dir;
        if((e=sb_get_inode(*sb, *id, &dir)) < 0) {
            return e;
        }
        DirEntry dentry;
        if((e=inode_find(dir, p, end-p-1, &dentry)) < 0) {
            idrop(dir);
            return e;
        }
        *id = dentry.id;
        *sb = dentry.superblock;
        idrop(dir);
        p = end;
    }
    *rest = p;
    return 0;
}
status_t vfs_find(Path* path, inodeid_t* id, Superblock** sb) {
    status_t e;
    Inode* dir;
    const char* filename;
    if((e=vfs_find_parent_inode(path, &dir, &filename)) < 0) {
        return e;
    }
    if(filename[0] == '\0') {
        *id = dir->id;
        *sb = dir->superblock;
        idrop(dir);
        return 0;
    }
    DirEntry dentry;
    if((e=inode_find(dir, filename, strlen(filename), &dentry)) < 0) {
        idrop(dir);
        return e;
    }
    idrop(dir);
    *id = dentry.id;
    *sb = dentry.superblock;
    return 0;
}
status_t vfs_open(Path* path, Inode** inode) {
    status_t e;
    inodeid_t id;
    Superblock* sb;
    if((e=vfs_find(path, &id, &sb)) < 0) {
        return e;
    }
    if((e=sb_get_inode(sb, id, inode)) < 0) {
        return e;
    }
    return 0;
}
// TODO: Checks for already exists for mkdir and create
status_t vfs_create(Path* path) {
    status_t e;
    Inode* dir;
    const char* filename;
    if((e=vfs_find_parent_inode(path, &dir, &filename)) < 0) {
        return e;
    }
    if((e=inode_create(dir, filename, strlen(filename))) < 0) {
        idrop(dir);
        return e;
    }
    idrop(dir);
    return 0;
}
status_t vfs_mkdir(Path* path) {
    status_t e;
    Inode* dir;
    const char* filename;
    if((e=vfs_find_parent_inode(path, &dir, &filename)) < 0) {
        return 0;
    }
    if((e=inode_mkdir(dir, filename, strlen(filename))) < 0) {
        idrop(dir);
        return e;
    }
    idrop(dir);
    return 0;
}
status_t init_vfs() {
    if(!(inode_cache=init_slab_cache(sizeof(Inode), "Inode"))) {
        kprint("ERROR: Failed to create inode cache\n");
        return -NOT_ENOUGH_MEMORY;
    }
    FileSystem* rootfs = get_rootfs();
    status_t e;
    if((e=rootfs->init(rootfs)) < 0) {
        kprint("ERROR: Failed to initialise rootfs: %d (%s)\n", (int)e, status_str(e));
        return e;
    }
    if((e=rootfs->mount(rootfs, &kernel.root_superblock, NULL)) < 0) {
        kprint("ERROR: Failed to mount rootfs: %d (%s)\n", (int)e, status_str(e));
        return e;
    }
    kprint("SUCCESS: Initialised rootfs\n");
    return 0;
}
