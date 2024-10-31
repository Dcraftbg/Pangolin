#include <memory.h>
#include <kernel.h>
#include <bootutils.h>
#include <kprint.h>
#include <mem/plist.h>

paddr_t kernel_alloc_phys_page() {
    void* addr = plist_allocate_page(&kernel.plist);
    if(addr) addr-=kernel.hhdm;
    return (paddr_t)addr;
}
void  kernel_dealloc_phys_page(paddr_t page) {
    plist_dealloc_page(&kernel.plist, ((void*)page)+kernel.hhdm);
}
paddr_t kernel_alloc_phys_pages(size_t pages) {
    void* addr = plist_allocate_cont_pages(&kernel.plist, pages);
    if(addr) addr-=kernel.hhdm;
    return (paddr_t)addr;
}
void  kernel_dealloc_phys_pages(paddr_t start, size_t pages) {
    plist_dealloc_cont_pages(&kernel.plist, ((void*)start)+kernel.hhdm, pages);
}

void* kernel_alloc_pages(size_t pages) {
    return plist_allocate_cont_pages(&kernel.plist, pages);
}
void kernel_dealloc_pages(void* addr, size_t pages) {
    plist_dealloc_cont_pages(&kernel.plist, addr, pages);
}
void init_mem() {
    kernel.hhdm = boot_get_hhdm();
    list_init(&kernel.plist.list);
    BootMemRegion region;
    for(size_t i = 0; i < boot_get_memregion_count(); ++i) {
        boot_get_memregion_at(&region, i);
        kprint("%zu> %p (%s) %zu pages\n", i, (void*)region.address, boot_memregion_kind_str(region.kind), region.size/PAGE_SIZE);
        if(region.kind == BOOT_MEMREGION_USABLE) {
            if(region.address < BOOT_HHDM_SIZE) {
                paddr_t region_end = region.address+region.size; 
                size_t pages_available = region.size/PAGE_SIZE;
                if(region_end > BOOT_HHDM_SIZE) 
                    pages_available = (BOOT_HHDM_SIZE-region.address)/PAGE_SIZE;
                void* region_virt = (void*)(region.address + kernel.hhdm);
                PListNode* node = region_virt;
                list_init(&node->list);
                node->pages = pages_available;
                list_append(&node->list, &kernel.plist.list);
            }
            else kprint("Available but ignored...\n");
        }
    }
}
