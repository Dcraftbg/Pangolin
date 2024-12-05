#include <kernel.h>
#include <mem/slab.h>
#include <mem/page.h>
#include <kprint.h>
#include <stddef.h>
#include <memory.h>
#include <string.h>

Cache *init_slab_cache(size_t obj_size, char *name) {
    char name_buf[20];
    strcpy(name_buf, name);
    if (strlen(name) > 19) {
        kprint("[WARNING] Slab cache of name \"%s\" is longer than the maximum cache name of twenty characters. "
                "It will be cut off to fit in the maximum size.\n", name_buf);
        name_buf[19] = 0;
    }
    
    size_t obj_per_slab = (page_align_up(obj_size + sizeof(Slab) + sizeof(uint64_t)) - sizeof(Slab)) / (obj_size + sizeof(uint64_t));

    Cache *new_cache = (Cache*) (kernel_alloc_phys_pages(bytes_to_pages(page_align_up(sizeof(Cache)))) + kernel.hhdm);
    
    *new_cache = (Cache) {
        .obj_size     = obj_size,
        .obj_per_slab = obj_per_slab,
    };
    
    strcpy(new_cache->name, name_buf);

    if (!kernel.slab_caches)
        list_init(&new_cache->list);
    else
        list_insert(&new_cache->list, kernel.slab_caches);
    
    struct list *slab_lists[] = {&new_cache->free_nodes,
                                 &new_cache->partial_nodes,
                                 &new_cache->full_nodes};
    for (size_t slab_list = 0; slab_list < 3; slab_list++) list_init(slab_lists[slab_list]);
    
    return new_cache;
}

void slab_grow(Cache *cache) {
    Slab *new_slab = (Slab*) ((uint64_t) kernel_alloc_phys_pages(bytes_to_pages(page_align_up(sizeof(Slab) + cache->obj_size * cache->obj_per_slab))) + kernel.hhdm);
    uint64_t stack_size = cache->obj_per_slab * sizeof(uint64_t);
    void *data_addr = (void*) ((uint64_t) new_slab + stack_size);
    *new_slab = (Slab) {
        .cache = cache,
        .free_stack_head = 0,
        .num_free = cache->obj_per_slab,
        .data = data_addr,
    };
    list_insert(&new_slab->list, &cache->free_nodes);
    // this loop is a little messy, sorry. 
    size_t data_element = 0;
    for (size_t stack_element = (uint64_t) new_slab + sizeof(Slab); stack_element < (uint64_t) data_addr; stack_element += 8) {
        *((uint64_t*) stack_element) = (uint64_t) data_addr + data_element;
        data_element += cache->obj_size;
    }
}

void *slab_alloc(Cache *cache) {
    Slab *slab = NULL;
    if (list_len(&cache->partial_nodes)) {
        slab = (Slab*) list_next(&cache->partial_nodes);
    } else if (list_len(&cache->free_nodes)) {
        slab = (Slab*) list_next(&cache->free_nodes);
    } else {
        slab_grow(cache);
        slab = (Slab*) list_next(&cache->free_nodes);
    }
    uint64_t *free_stack = (uint64_t*) ((uint64_t) slab + sizeof(Slab));
    void *free_stack_element = (void*) free_stack[slab->free_stack_head];
    slab->free_stack_head++;
    slab->num_free--;
    if (!slab->num_free) {
        list_remove(&slab->list);
        list_insert(&slab->list, &cache->full_nodes);
    } else if (slab->num_free < cache->obj_per_slab && (struct list*) slab != &cache->partial_nodes) {
        list_remove(&slab->list);
        list_insert(&slab->list, &cache->partial_nodes);
    }
    return free_stack_element;
}
