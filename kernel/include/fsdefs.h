#pragma once
#include <stdint.h>
#include <stddef.h>

typedef uint64_t inodeid_t;
typedef intptr_t off_t;

enum {
    INODE_FILE,
    INODE_DIR,
};
typedef int inodekind_t;
