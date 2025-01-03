#pragma once
#include <status.h>
#include <fsdefs.h>
#include <mem/slab.h>

typedef struct Inode Inode;
typedef struct InodeOps InodeOps;
typedef struct Superblock Superblock;
typedef struct SuperblockOps SuperblockOps;
typedef struct DirEntry DirEntry;
typedef struct DirEntryOps DirEntryOps;
typedef struct FileSystem FileSystem;
typedef struct FsFuture FsFuture;
typedef struct Path Path;
struct FsFuture {
    Superblock* superblock;
    status_t (*complete)(FsFuture* future);
    void* priv;
};
// fsfuture for instant completion for file systems that don't implement async
static inline status_t fsfuture_instant_complete(FsFuture* future) {
    return (status_t)future->priv;
}
static inline void fsfuture_instant(FsFuture* future, Superblock* superblock, status_t status) {
    future->superblock = superblock;
    future->complete = fsfuture_instant_complete;
    future->priv = (void*)status;
}

struct InodeOps {
    status_t (*schedule_write)(Inode* inode, const void* data, off_t offset, size_t size, FsFuture* future);
    status_t (*schedule_read) (Inode* inode, void* data      , off_t offset, size_t size, FsFuture* future);
    status_t (*create)(Inode* dir, const char* name, size_t namelen);
    status_t (*mkdir)(Inode* dir, const char* name, size_t namelen);
    status_t (*find)(Inode* dir, const char* name, size_t namelen, DirEntry* direntry);
    status_t (*schedule_get_dir_entries)(Inode* dir, DirEntry* entries, off_t offset, size_t count, FsFuture* future);
    status_t (*cleanup)(Inode* inode);
};
struct Inode {
    Superblock *superblock;
    ino_t id;
    inodekind_t kind;
    size_t shared;
    InodeOps *ops;
    void *priv;
};
struct DirEntry {
    Superblock *superblock;
    ino_t id;
    DirEntryOps *ops;
    void *priv;
};
struct DirEntryOps {
    status_t (*identify)(DirEntry* entry, char* name, size_t namecap);
    status_t (*cleanup)(DirEntry* entry);
};
struct Superblock {
    FileSystem *filesystem;
    SuperblockOps *ops;
    ino_t root;
    void *priv;
};
struct SuperblockOps {
    status_t (*unmount)(Superblock* superblock);
    status_t (*get_inode)(Superblock* superblock, ino_t id, Inode** inode);
};
struct FileSystem {
    status_t (*init)(FileSystem* fs);
    status_t (*mount)(FileSystem* fs, Superblock* superblock, Inode* file);
    status_t (*deinit)(FileSystem* fs);
    void *priv;
};

extern Cache* inode_cache;

// Inode wrappers
status_t inode_schedule_write(Inode* inode, const void* data, off_t offset, size_t size, FsFuture* future);
static status_t inode_write(Inode* inode, const void* data, off_t offset, size_t size) {
    status_t e;
    FsFuture future;
    if((e=inode_schedule_write(inode, data, offset, size, &future)) < 0) return e;
    while((e=future.complete(&future)) == -PENDING);
    return e;
}
status_t inode_schedule_read(Inode* inode, void* data      , off_t offset, size_t size, FsFuture* future);
static status_t inode_read(Inode* inode, void* data, off_t offset, size_t size) {
    status_t e;
    FsFuture future;
    if((e=inode_schedule_read(inode, data, offset, size, &future)) < 0) return e;
    while((e=future.complete(&future)) == -PENDING);
    return e;
}
status_t inode_create(Inode* dir, const char* name, size_t namelen);
status_t inode_mkdir (Inode* dir, const char* name, size_t namelen);
status_t inode_find(Inode* dir, const char* name, size_t namelen, DirEntry* direntry);
status_t inode_schedule_get_dir_entries(Inode* dir, DirEntry* entries, off_t offset, size_t count, FsFuture* future);
status_t inode_cleanup(Inode* inode);

// Superblock wrappers
status_t sb_unmount(Superblock* superblock);
status_t sb_get_inode(Superblock* superblock, ino_t id, Inode** inode);

// DirEntry wrappers
status_t direntry_identify(DirEntry* entry, char* name, size_t namecap);
status_t direntry_cleanup(DirEntry* entry);



static inline Inode* inode_new(Superblock* superblock, ino_t id, inodekind_t kind, InodeOps* ops, void *priv) {
    Inode* me = slab_alloc(inode_cache);
    if(!me) return NULL;
    me->superblock = superblock;
    me->id = id;
    me->kind = kind;
    me->ops = ops;
    me->priv = priv;
    me->shared = 1;
    return me;
}
static inline Inode* iget(Inode* inode) {
    return (inode->shared++, inode);
}
static inline void idrop(Inode* inode) {
    if(--inode->shared == 0) {
        inode_cleanup(inode);
    }
}


status_t init_vfs();

struct Path {
    struct {
        Superblock* superblock;
        ino_t inode;
    } from;
    const char* path;
};

status_t vfs_find_parent(Path* path, ino_t* id, Superblock** sb, const char** rest);
static status_t vfs_find_parent_inode(Path* path, Inode** inode, const char** rest) {
    status_t e;
    ino_t parent_id;
    Superblock* parent_sb;
    if((e=vfs_find_parent(path, &parent_id, &parent_sb, rest)) < 0) {
        return e;
    }
    if((e=sb_get_inode(parent_sb, parent_id, inode)) < 0) {
        return e;
    }
    return 0;
}
status_t vfs_find(Path* path, ino_t* id, Superblock** sb);
status_t vfs_open(Path* path, Inode** inode);
status_t vfs_create(Path* path);
status_t vfs_mkdir(Path* path);
#define path_abs(_path) (Path){.from={.superblock=&kernel.root_superblock, .inode=kernel.root_superblock.root}, .path=_path}
status_t parse_abs(const char* path, Path* result);

// Abs version of functions. Used mainly by the kernel and for initrd
static status_t vfs_open_abs(const char* path, Inode** inode) {
    status_t e;
    Path p;
    if((e=parse_abs(path, &p)) < 0) return e;
    return vfs_open(&p, inode);
}
static status_t vfs_create_abs(const char* path) {
    status_t e;
    Path p;
    if((e=parse_abs(path, &p)) < 0) return e;
    return vfs_create(&p);
}
static status_t vfs_mkdir_abs(const char* path) {
    status_t e;
    Path p;
    if((e=parse_abs(path, &p)) < 0) return e;
    return vfs_mkdir(&p);
}
