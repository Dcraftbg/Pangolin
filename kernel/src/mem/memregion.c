#include <memory.h>
#include <mem/page.h>
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

/* Copies a Memregion from an old page tree to a new page tree and returns the Memregion which can then be
 * inserted into the list of the new task. If it's mapped as read-only, then it should simply map it into the new 
 * memory space, but otherwise it should copy the data as well.
 */
Memregion *memregion_clone(Memregion *original, page_t old_page_tree, page_t new_page_tree) {
    if (original->flags & KERNEL_PFLAG_WRITE) {
        // copy data and map
        void *dest = kernel_alloc_pages(original->num_pages);
        size_t bytes_to_copy = page_align_up(original->num_pages) / 4096;
        read_vmem(old_page_tree, original->addr, dest, bytes_to_copy);
        page_mmap(new_page_tree, (uint64_t) dest - kernel.hhdm, original->addr, original->num_pages, original->flags);
    } else {
        paddr_t phys = virt_to_phys(old_page_tree, original->addr);
        page_mmap(new_page_tree, phys, original->addr, original->num_pages, original->flags);
    }
    return original;
}

Memregion *memregion_find(Memregion *list, uintptr_t addr) {
    list_foreach(i, &list->list) {
        if (((Memregion*) i)->addr == addr)
            return (Memregion*) i;
    }
    return NULL;
}
