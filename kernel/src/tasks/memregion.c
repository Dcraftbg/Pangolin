#include <mem/memregion.h>
#include <mem/slab.h>
#include <kernel.h>
#include <kprint.h>
#include <cpu.h>

void init_memregion() {
    kernel.memregion_cache = init_slab_cache(sizeof(Memregion), "Memregion Cache");
    if (!kernel.memregion_cache) {
        kprint("Failed to initialise memregion.\n");
        HALT_DEVICE();
    }
    kprint("Initialised memregion.\n");
}

/* NOTE: There is no new_memregion_list or anything similar.
 * This is because you pass add_memregion a pointer to a Memregion*, and if it's null, then it'll initialise a new list.
 * Otherwise it just adds a new memregion to the list as normal.
 */
Memregion *add_memregion(Memregion **list, uintptr_t addr, size_t num_pages, pageflags_t flags) {
    Memregion *new_memregion = (Memregion*) slab_alloc(kernel.memregion_cache);
    if (!*list) {
        list_init(&new_memregion->list);
        *list = new_memregion;
    } else {
        list_insert(&new_memregion->list, &(*list)->list);
    }
    new_memregion->addr      = addr;
    new_memregion->num_pages = num_pages;
    new_memregion->flags     = flags;
    return new_memregion;
}

void delete_memregion(Memregion *element) {
    list_remove(&element->list);
    slab_free(kernel.memregion_cache, element);
}

void delete_memregion_list(Memregion **list) {
    for (struct list *iter = &(*list)->list; iter != iter->next;) {
        iter = iter->next;
        list_remove(iter);
        slab_free(kernel.memregion_cache, (Memregion*) iter);
    }
    slab_free(kernel.memregion_cache, *list); // delete the final one as well
    *list = 0;
}
