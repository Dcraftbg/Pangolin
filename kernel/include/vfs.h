#pragma once
#include <status.h>
#include <fsdefs.h>
typedef struct Inode Inode;
typedef struct InodeOps InodeOps;
typedef struct Superblock Superblock;
typedef struct SuperblockOps SuperblockOps;
typedef struct DirEntry DirEntry;
typedef struct DirEntryOps DirEntryOps;
typedef struct FileSystem FileSystem;
typedef struct FsFuture FsFuture;
struct FsFuture {
    Superblock* superblock;
    status_t (*complete)(FsFuture* future);
    void* priv;
};
struct InodeOps {
    status_t (*create)(Inode* dir, const char* name);
    status_t (*mkdir)(Inode* dir, const char* name);

    status_t (*open) (Inode* inode, Inode** file);
    status_t (*schedule_write)(Inode* inode, const void* data, size_t size, FsFuture* future);
    status_t (*schedule_read) (Inode* inode, void* data      , size_t size, FsFuture* future);
    status_t (*close)(Inode* inode);

    status_t (*diropen)(Inode* inode, Inode** dir);
    status_t (*schedule_get_dir_entries)(Inode* dir, DirEntry* entry, size_t count, FsFuture* future);
    status_t (*dirclose)(Inode* inode);
};
struct Inode {
    Superblock *superblock;
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
    FileSystem* filesystem;
    SuperblockOps *ops;
    void *priv;
};
struct SuperblockOps {
    status_t (*unmount)(Superblock* superblock);
};
struct FileSystem {
    status_t (*init)(FileSystem* fs);
    status_t (*mount)(FileSystem* fs, Superblock* superblock, Inode* file);
    status_t (*deinit)(FileSystem* fs);
    void *priv;
};
