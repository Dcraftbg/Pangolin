#pragma once
#include <list.h>
#include <stddef.h>

typedef struct Cache Cache;
typedef struct Slab Slab;

struct Cache {
    struct list list;
    char   name[20];
    struct list free_nodes;
    struct list partial_nodes;
    struct list full_nodes;
    size_t obj_size;
    size_t obj_per_slab;
};

struct Slab {
    struct list list;
    Cache  *cache;
    size_t free_stack_head;
    void   *data;
    // Free stack comes immediately after, then the data
};

void init_slab_cache(size_t obj_size, size_t num_obj, size_t obj_per_slab, char *name);
