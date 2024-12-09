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
static inline status_t fsfuture_instant_complete(FsFuture* _future) {
    (void)_future;
    return 0;
}
static inline void fsfuture_instant(FsFuture* future, Superblock* superblock) {
    future->superblock = superblock;
    future->complete = fsfuture_instant_complete;
    future->priv = NULL;
}

struct InodeOps {
    status_t (*schedule_write)(Inode* inode, const void* data, off_t offset, size_t size, FsFuture* future);
    status_t (*schedule_read) (Inode* inode, void* data      , off_t offset, size_t size, FsFuture* future);
    status_t (*create)(Inode* dir, const char* name, size_t namelen);
    status_t (*mkdir)(Inode* dir, const char* name, size_t namelen);
    status_t (*schedule_get_dir_entries)(Inode* dir, DirEntry* entries, off_t offset, size_t count, FsFuture* future);
    status_t (*cleanup)(Inode* inode);
};
struct Inode {
    Superblock *superblock;
    inodeid_t id;
    inodekind_t kind;
    size_t shared;
    InodeOps *ops;
    void *priv;
};
struct DirEntry {
    Superblock *superblock;
    DirEntryOps *ops;
    void *priv;
};
struct DirEntryOps {
    status_t (*identify)(DirEntry* entry, char* name, size_t namecap);
    status_t (*get_inode)(DirEntry* entry, Inode **inode);
    status_t (*cleanup)(DirEntry* entry);
};
struct Superblock {
    FileSystem *filesystem;
    SuperblockOps *ops;
    inodeid_t root;
    void *priv;
};
struct SuperblockOps {
    status_t (*unmount)(Superblock* superblock);
    status_t (*get_inode)(Superblock* superblock, inodeid_t id, Inode** inode);
};
struct FileSystem {
    status_t (*init)(FileSystem* fs);
    status_t (*mount)(FileSystem* fs, Superblock* superblock, Inode* file);
    status_t (*deinit)(FileSystem* fs);
    void *priv;
};

extern Cache* inode_cache;
static inline Inode* inode_new(Superblock* superblock, inodeid_t id, inodekind_t kind, InodeOps* ops, void *priv) {
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
        if(inode->ops->cleanup) inode->ops->cleanup(inode);
    }
}
status_t init_vfs();

struct Path {
    struct {
        Superblock* superblock;
        inodeid_t inode;
    } from;
    const char* path;
};
#define path_abs(_path) (Path){.from={.superblock=&kernel.root_superblock, .inode=kernel.root_superblock.root}, .path=_path}
status_t parse_abs(const char* path, Path* result);
