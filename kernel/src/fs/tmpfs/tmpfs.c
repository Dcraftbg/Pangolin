#include <fs/tmpfs/tmpfs.h>
static InodeOps inode_ops = {0};
static DirEntryOps direntry_ops = {0};
static SuperblockOps superblock_ops = {0};
status_t tmpfs_init(FileSystem* _fs) {
    (void)_fs;
    return 0;
}
status_t tmpfs_deinit(FileSystem* _fs) {
    (void)_fs;
    return 0;
}
status_t tmpfs_mount(FileSystem* fs, Superblock* superblock, Inode* file) {
    (void)fs;
    (void)superblock;
    (void)file;
    (void)inode_ops;
    (void)direntry_ops;
    (void)superblock_ops;
    if(!file) return -INVALID_PARAM;
    return -UNSUPPORTED;
}
FileSystem tmp_fs = {
    .init   = tmpfs_init,
    .mount  = tmpfs_mount,
    .deinit = tmpfs_deinit,
    .priv   = NULL,
};
