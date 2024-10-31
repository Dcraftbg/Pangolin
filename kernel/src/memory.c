#include <memory.h>
#include <kernel.h>
#include <bootutils.h>
#include <kprint.h>

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
