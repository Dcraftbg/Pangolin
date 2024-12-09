#include <fs/tmpfs/tmpfs.h>
typedef struct TmpfsData TmpfsData;
typedef struct TmpfsDirEntry TmpfsDirEntry;
struct TmpfsData {
    TmpfsData* next;
    char data[];
};
#define DENTS_PER_BLOCK ((PAGE_SIZE-sizeof(TmpfsData))/sizeof(TmpfsDirEntry*))
typedef struct {
    size_t      size;
    inodekind_t kind;
    TmpfsData*  data;
} TmpfsInode;
struct TmpfsDirEntry {
    char name[MAX_TMPFS_NAME];
    TmpfsInode* inode;
};
static Cache* tmpfs_inode_cache    = NULL;
static Cache* tmpfs_direntry_cache = NULL;
static TmpfsData* datablock_new() {
    TmpfsData* data = (TmpfsData*)kernel_alloc_pages(1);
    if(!data) return NULL;
    data->next = NULL;
    memset(data->data, 0, PAGE_SIZE-sizeof(*data));
    return data;
}
static void datablock_destroy(TmpfsData* data) {
    kernel_dealloc_pages(data, 1);
}

static inline TmpfsInode* tmpfs_new_inode(size_t size, inodekind_t kind, TmpfsData* data) {
    TmpfsInode* me = slab_alloc(tmpfs_inode_cache);
    if(!me) return NULL;
    me->size = size;
    me->kind = kind;
    me->data = data;
    return me;
}
// NOTE: DOES NOT CLEANUP SUBENTRIES FOR DIRECTORIES.
// THIS IS INTENTIONAL. You'll need to call tmpfs_dentry_destroy on every entry.
// So this will not be recursive
static void tmpfs_inode_destroy(TmpfsInode* inode) {
    TmpfsData* head = inode->data;
    while(head) {
        TmpfsData* next = head->next;
        datablock_destroy(head);
        head = next;
    }
    slab_free(tmpfs_inode_cache, inode);
}
static TmpfsInode* directory_new() {
    return tmpfs_new_inode(0, INODE_DIR, NULL);
}
static TmpfsInode* file_new() {
    return tmpfs_new_inode(0, INODE_FILE, NULL);
}
static TmpfsDirEntry* tmpfs_dentry_new(const char* name, size_t namelen, TmpfsInode* inode) {
    TmpfsDirEntry* me = slab_alloc(tmpfs_direntry_cache);
    if(!me) return NULL;
    memcpy(me->name, name, namelen);
    me->name[namelen] = '\0';
    me->inode = inode;
    return me;
}
static void tmpfs_dentry_destroy(TmpfsDirEntry* entry) {
    if(entry->inode) {
        tmpfs_inode_destroy(entry->inode);
        entry->inode = NULL;
    }
    slab_free(tmpfs_direntry_cache, entry);
}

static DirEntryOps tmpfs_direntry_ops = {
    0
};
static status_t tmpfs_put(TmpfsInode* dir, TmpfsDirEntry* new_entry) {
    TmpfsData* prev = (TmpfsData*)(&(dir->data));
    TmpfsData* head = dir->data;
    size_t size = dir->size;
    while(head && size >= DENTS_PER_BLOCK) {
        size -= DENTS_PER_BLOCK;
        prev = head;
        head = head->next;
    }
    if(size >= DENTS_PER_BLOCK) return -FILE_CORRUPTION;
    if(!head) {
        TmpfsData* new_block = datablock_new();
        if(!new_block) return -NOT_ENOUGH_MEMORY;
        prev->next = new_block;
        head = new_block;
    }
    ((TmpfsDirEntry**)head->data)[size] = new_entry;
    dir->size++;
    return 0;
}
static status_t tmpfs_create(Inode* dir, const char* name, size_t namelen) {
    if(dir->kind != INODE_DIR) return -INVALID_KIND;
    if(namelen > MAX_TMPFS_NAME) return -NAME_TOO_LONG;
    TmpfsInode* file = file_new();
    if(!file) return -NOT_ENOUGH_MEMORY;
    TmpfsDirEntry* entry = tmpfs_dentry_new(name, namelen, file);
    if(!entry) {
        tmpfs_inode_destroy(file);
        return -NOT_ENOUGH_MEMORY;
    }
    // file is now moved to entry. It will be in charge of its cleanup.
    status_t e = tmpfs_put(dir->priv, entry);
    if(e < 0) {
        tmpfs_dentry_destroy(entry);
        return e;
    }
    return 0;
}
static status_t tmpfs_mkdir(Inode* dir, const char* name, size_t namelen) {
    if(dir->kind != INODE_DIR) return -INVALID_KIND;
    if(namelen > MAX_TMPFS_NAME) return -NAME_TOO_LONG;
    TmpfsInode* file = directory_new();
    if(!file) return -NOT_ENOUGH_MEMORY;
    TmpfsDirEntry* entry = tmpfs_dentry_new(name, namelen, file);
    if(!entry) {
        tmpfs_inode_destroy(file);
        return -NOT_ENOUGH_MEMORY;
    }
    // file is now moved to entry. It will be in charge of its cleanup.
    status_t e = tmpfs_put(dir->priv, entry);
    if(e < 0) {
        tmpfs_dentry_destroy(entry);
        return e;
    }
    return 0;
}
static status_t tmpfs_schedule_get_dir_entries(Inode* dir, DirEntry* entries, off_t offset, size_t count, FsFuture* future) {
    TmpfsInode* inode = dir->priv;
    if(dir->kind != INODE_DIR) return -INVALID_KIND;
    if((size_t)offset > inode->size) return -INVALID_OFFSET;
    if((size_t)offset == inode->size) return 0;
    TmpfsData* head = inode->data;
    while(head && (size_t)offset >= DENTS_PER_BLOCK) {
        offset -= DENTS_PER_BLOCK;
        head = head->next;
    }
    if(!head) return -FILE_CORRUPTION;
    size_t left = inode->size-offset;
    if(count > left) count=left;
    size_t read = 0;
    while(head && read < count) {
        left = count-read;
        if(left > DENTS_PER_BLOCK) left = DENTS_PER_BLOCK;
        for(size_t i = 0; i < left; ++i) {
            DirEntry* entry = &entries[read+i];
            entry->superblock = dir->superblock;
            entry->ops        = &tmpfs_direntry_ops;
            entry->priv       = ((TmpfsDirEntry**)head->data)[i];
        }
        read += left;
        head = head->next;
    }
    fsfuture_instant(future, dir->superblock);
    return read;
}


static InodeOps tmpfs_inode_ops = {
    .create                   = tmpfs_create,
    .mkdir                    = tmpfs_mkdir,
    .schedule_get_dir_entries = tmpfs_schedule_get_dir_entries,
};

static status_t tmpfs_unmount(Superblock* superblock) {
    (void)superblock;
    // TODO: deallocate all memory of tmpfs from superblock->root
    return 0;
}
static status_t tmpfs_get_inode(Superblock* superblock, inodeid_t id, Inode** inode) {
    TmpfsInode* tmp_inode = (TmpfsInode*)id;
    *inode = inode_new(superblock, id, tmp_inode->kind, &tmpfs_inode_ops, tmp_inode);
    return 0;
}
static SuperblockOps tmpfs_superblock_ops = {
    .unmount = tmpfs_unmount,
    .get_inode = tmpfs_get_inode,
};


static status_t tmpfs_mount(FileSystem* fs, Superblock* superblock, Inode* file) {
    (void)fs;
    if(file) return -INVALID_PARAM;
    TmpfsInode* root = directory_new();
    superblock->root = (inodeid_t)root;
    superblock->priv = root;
    superblock->ops  = &tmpfs_superblock_ops;
    return 0;
}
static status_t tmpfs_init(FileSystem* _fs) {
    (void)_fs;
    if(!(tmpfs_inode_cache = init_slab_cache(sizeof(TmpfsInode), "TmpfsInode"))) 
        return -NOT_ENOUGH_MEMORY;
    // TODO: cleanup tmpfs_inode_cache in case tmpfs_direntry_cache fails
    if(!(tmpfs_inode_cache = init_slab_cache(sizeof(TmpfsDirEntry), "TmpfsDirEntry"))) 
        return -NOT_ENOUGH_MEMORY;
    return 0;

}
static status_t tmpfs_deinit(FileSystem* _fs) {
    (void)_fs;
    // TODO: cache_destoy on tmpfs_inode_cache
    return 0;
}
FileSystem tmp_fs = {
    .init   = tmpfs_init,
    .mount  = tmpfs_mount,
    .deinit = tmpfs_deinit,
    .priv   = NULL,
};
