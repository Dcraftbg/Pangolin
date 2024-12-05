#include <kernel.h>
#include <mem/slab.h>
#include <mem/page.h>
#include <kprint.h>
#include <stddef.h>
#include <memory.h>
#include <string.h>

/* A function to initialise a new slab cache.
 * TODO: Calculate obj_per_slab instead of taking it as an argument. */
Cache *init_slab_cache(size_t obj_size, char *name) {
    char name_buf[20];
    strcpy(name_buf, name);
    if (strlen(name) > 19) {
        kprint("[WARNING] Slab cache of name \"%s\" is longer than the maximum cache name of twenty characters. "
                "It will be cut off to fit in the maximum size.\n", name_buf);
        name_buf[19] = 0;
    }
    
    size_t obj_per_slab = (page_align_up(obj_size + sizeof(Slab) + sizeof(uint64_t)) - sizeof(Slab)) / (obj_size + sizeof(uint64_t));
    size_t num_obj = obj_per_slab;

    kprint("Initialising new slab cache: \"%s\" of object size %zu with %zu objects, with %zu objects per slab.\n",
            name_buf, obj_size, num_obj, obj_per_slab);
    
    size_t stack_size = num_obj * sizeof(uint64_t);
    size_t num_slabs = 1;
    size_t cache_size = sizeof(Cache) + // size added from the cache
                        sizeof(Slab) * num_slabs + // size added from the slabs metadata
                        obj_size * num_obj + // size added from the actual data
                        stack_size; // size added from the free stack.
    Cache *new_cache = (Cache*) (kernel_alloc_phys_pages(bytes_to_pages(page_align_up(cache_size))) + kernel.hhdm);
    kprint("New cache addr: %p, with %zu slabs and %zu byte cache size.\n", new_cache, num_slabs, cache_size);
    
    *new_cache = (Cache) {
        .obj_size     = obj_size,
        .obj_per_slab = obj_per_slab,
    };
    strcpy(new_cache->name, name_buf);

    if (!kernel.slab_caches) {
        kprint("Slab object list is empty, must initiate list.\n");
        list_init(&new_cache->list);
    } else {
        list_insert(&new_cache->list, kernel.slab_caches);
    }
    
    struct list *slab_lists[] = {&new_cache->free_nodes,
                                 &new_cache->partial_nodes,
                                 &new_cache->full_nodes};
    for (size_t slab_list = 0; slab_list < 3; slab_list++) list_init(slab_lists[slab_list]);
    
    size_t slab_size = sizeof(Slab) + // slab size itself
                       obj_size * obj_per_slab + // size of the data
                       stack_size; // size of the stack
                       
    
    for (size_t slab = 0; slab < num_slabs; slab++) {
        Slab *new_slab = (Slab*) ((size_t) new_cache + sizeof(Cache) + (slab_size * slab));
        void* data_addr = (void*) ((uint64_t) new_slab + stack_size);
        *new_slab = (Slab) {
            .cache = new_cache,
            .free_stack_head = 0,
            .num_free = obj_per_slab,
            .data = data_addr,
        };
        list_insert(&new_slab->list, &new_cache->free_nodes);
        
        // this loop is a little messy, sorry. 
        size_t data_element = 0;
        for (size_t stack_element = (uint64_t) new_slab + sizeof(Slab); stack_element < (uint64_t) data_addr; stack_element += 8) {
            *((uint64_t*) stack_element) = (uint64_t) data_addr + data_element;
            data_element += obj_size;
        }
    }
    
    return new_cache;
}

void *slab_alloc(Cache* cache) {
    Slab *slab = NULL;
    if (list_len(&cache->partial_nodes)) {
        slab = (Slab*) list_next(&cache->partial_nodes);
    } else if (list_len(&cache->free_nodes)) {
        slab = (Slab*) list_next(&cache->free_nodes);
    } else
        return NULL;
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










