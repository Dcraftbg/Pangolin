#pragma once
#include <list.h>
#include <stdint.h>
#include <mem/page.h>

typedef struct {
    struct list list;
    pageflags_t flags;
    uintptr_t   addr;
    size_t      num_pages;
} Memregion;

void init_memregion();
// See the note in memregion.c
Memregion *add_memregion(Memregion **list, uintptr_t addr, size_t num_pages, pageflags_t flags);
void delete_memregion_list(Memregion **list);
void delete_memregion(Memregion *element);
Memregion *memregion_clone(Memregion *original, page_t old_page_tree, page_t new_page_tree);
