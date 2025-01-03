#pragma once
#include <stdint.h>
#include <stddef.h>

// NOTE: defined in ../../usr/include
#include <sys/types.h>
#include <dirent.h>

enum {
    INODE_FILE,
    INODE_DIR,
};
typedef int inodekind_t;
