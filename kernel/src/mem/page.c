// NOTE: Inspired by a project of mine (Dcraftbg) MinOS: https://github.com/Dcraftbg/MinOS/blob/master/kernel/src/page.c
// Parts licensed under MIT
#include <mem/page.h>
#include <memory.h>
#include <bootutils.h>
#include <kernel.h>
#include <string.h>
#include <kpanic.h>
#include <kprint.h>
#include <utils.h>

#define PAGE_MASK 0xFFFF000000000000
bool page_mmap(page_t pml4_addr, uintptr_t phys, uintptr_t virt, size_t pages_count, pageflags_t flags) {
    virt &= ~PAGE_MASK;          // Clean up the top bits (reasons I won't get into)
    uint16_t pml1 = (virt >> (12   )) & 0x1ff;
    uint16_t pml2 = (virt >> (12+9 )) & 0x1ff;
    uint16_t pml3 = (virt >> (12+18)) & 0x1ff;
    uint16_t pml4 = (virt >> (12+27)) & 0x1ff;
    for(; pml4 < KERNEL_PAGE_ENTRIES; pml4++) {
        page_t pml3_addr = NULL;
        if(pml4_addr[pml4] == 0) {
            pml4_addr[pml4] = kernel_alloc_phys_page();
            if(!pml4_addr[pml4]) return false; // Out of memory
            pml3_addr = (page_t)(pml4_addr[pml4] + kernel.hhdm); 
            memset(pml3_addr, 0, PAGE_SIZE);
            pml4_addr[pml4] |= KERNEL_PFLAG_WRITE | KERNEL_PFLAG_PRESENT | (flags & KERNEL_PFLAG_USER);
        } else {
            pml3_addr = (page_t)page_align_down(pml4_addr[pml4] + kernel.hhdm);
        }

        for(; pml3 < KERNEL_PAGE_ENTRIES; pml3++) {
            page_t pml2_addr = NULL;
            if(pml3_addr[pml3] == 0) {
                pml3_addr[pml3] = kernel_alloc_phys_page();
                if(!pml3_addr[pml3]) return false; // Out of memory
                pml2_addr = (page_t)(pml3_addr[pml3] + kernel.hhdm); 
                memset(pml2_addr, 0, PAGE_SIZE);
                pml3_addr[pml3] |= KERNEL_PFLAG_WRITE | KERNEL_PFLAG_PRESENT | (flags & KERNEL_PFLAG_USER);
            } else {
                pml2_addr = (page_t)page_align_down(pml3_addr[pml3] + kernel.hhdm);
            }

            for(; pml2 < KERNEL_PAGE_ENTRIES; pml2++) {
                page_t pml1_addr = NULL;
                if(pml2_addr[pml2] == 0) {
                    pml2_addr[pml2] = kernel_alloc_phys_page();
                    if(!pml2_addr[pml2]) return false; // Out of memory
                    pml1_addr = (page_t)(pml2_addr[pml2] + kernel.hhdm); 
                    memset(pml1_addr, 0, PAGE_SIZE);
                    pml2_addr[pml2] |= KERNEL_PFLAG_WRITE | KERNEL_PFLAG_PRESENT | (flags & KERNEL_PFLAG_USER);
                } else {
                    pml1_addr = (page_t)page_align_down(pml2_addr[pml2] + kernel.hhdm);
                }

                for(; pml1 < KERNEL_PAGE_ENTRIES; pml1++) {
                    // if(pml1_addr[pml1] != 0) {
                    //     // printf("Memory already mapped!");
                    //     return false; // Memory already allocated 
                    // }
                    pml1_addr[pml1] = phys | flags;
                    pages_count--;
                    phys += PAGE_SIZE;
                    if(pages_count==0) return true; // We filled up everything
                }
                pml1 = 0;
            }
            pml2 = 0;
        }
        pml3 = 0;
    }
    return pages_count == 0;
}

bool page_alloc(page_t pml4_addr, uintptr_t virt, size_t pages_count, pageflags_t flags) {
    virt &= ~PAGE_MASK;
    uint16_t pml1 = (virt >> (12   )) & 0x1ff;
    uint16_t pml2 = (virt >> (12+9 )) & 0x1ff;
    uint16_t pml3 = (virt >> (12+18)) & 0x1ff;
    uint16_t pml4 = (virt >> (12+27)) & 0x1ff;
    for(; pml4 < KERNEL_PAGE_ENTRIES; pml4++) {
        page_t pml3_addr = NULL;
        if(pml4_addr[pml4] == 0) {
            pml4_addr[pml4] = kernel_alloc_phys_page();
            if(!pml4_addr[pml4]) return false; // Out of memory
            pml3_addr = (page_t)(pml4_addr[pml4] + kernel.hhdm); 
            memset(pml3_addr, 0, PAGE_SIZE);
            pml4_addr[pml4] |= KERNEL_PFLAG_WRITE | KERNEL_PFLAG_PRESENT | (flags & KERNEL_PFLAG_USER);
        } else {
            pml3_addr = (page_t)page_align_down(pml4_addr[pml4] + kernel.hhdm);
        }

        for(; pml3 < KERNEL_PAGE_ENTRIES; pml3++) {
            page_t pml2_addr = NULL;
            if(pml3_addr[pml3] == 0) {
                pml3_addr[pml3] = kernel_alloc_phys_page();
                if(!pml3_addr[pml3]) return false; // Out of memory
                pml2_addr = (page_t)(pml3_addr[pml3] + kernel.hhdm); 
                memset(pml2_addr, 0, PAGE_SIZE);
                pml3_addr[pml3] |= KERNEL_PFLAG_WRITE | KERNEL_PFLAG_PRESENT | (flags & KERNEL_PFLAG_USER);
            } else {
                pml2_addr = (page_t)page_align_down(pml3_addr[pml3] + kernel.hhdm);
            }

            for(; pml2 < KERNEL_PAGE_ENTRIES; pml2++) {
                page_t pml1_addr = NULL;
                if(pml2_addr[pml2] == 0) {
                    pml2_addr[pml2] = kernel_alloc_phys_page();
                    if(!pml2_addr[pml2]) return false; // Out of memory
                    pml1_addr = (page_t)(pml2_addr[pml2] + kernel.hhdm); 
                    memset(pml1_addr, 0, PAGE_SIZE);
                    pml2_addr[pml2] |= KERNEL_PFLAG_WRITE | KERNEL_PFLAG_PRESENT | (flags & KERNEL_PFLAG_USER);
                } else {
                    pml1_addr = (page_t)page_align_down(pml2_addr[pml2] + kernel.hhdm);
                }

                for(; pml1 < KERNEL_PAGE_ENTRIES; pml1++) {
#if 0
                    if(pml1_addr[pml1] != 0) {
                        printf("Memory already allocated!\n");
                        return false; // Memory already allocated 
                    }
#endif
                    if(pml1_addr[pml1] == 0) {
                        pml1_addr[pml1] = kernel_alloc_phys_page();
                        if(pml1_addr[pml1] == 0) return false;
                        pml1_addr[pml1] |= flags | KERNEL_PFLAG_PRESENT;
                    }
                    pages_count--;
                    if(pages_count==0) return true; // We filled up everything
                }
                pml1 = 0;
            }
            pml2 = 0;
        }
        pml3 = 0;
    }
    return pages_count == 0;
}

paddr_t virt_to_phys(page_t pml4_addr, uint64_t virt_addr) {
    virt_addr &= ~PAGE_MASK;
    uint64_t pml1 = (virt_addr >> 12) & 511;
    uint64_t pml2 = (virt_addr >> (12 + 9)) & 511;
    uint64_t pml3 = (virt_addr >> (12 + 18)) & 511;
    uint64_t pml4 = (virt_addr >> (12 + 27)) & 511;
    for (; pml4 < 512; pml4++) {
        uint64_t *pml3_addr = NULL;
        if (pml4_addr[pml4] == 0)
            return 0;
        else
            pml3_addr = (uint64_t*)(page_align_down(pml4_addr[pml4]) + kernel.hhdm);

        for (; pml3 < 512; pml3++) {
            uint64_t *pml2_addr = NULL;
            if (pml3_addr[pml3] == 0)
                return 0;
            else
                pml2_addr = (uint64_t*)(page_align_down(pml3_addr[pml3]) + kernel.hhdm);

            for (; pml2 < 512; pml2++) {
                uint64_t *pml1_addr = NULL;
                if (pml2_addr[pml2] == 0)
                    return 0;
                else
                    pml1_addr = (uint64_t*)(page_align_down(pml2_addr[pml2]) + kernel.hhdm);
                
                if (pml1_addr[pml1] == 0)
                    return 0;

                return (uint64_t)(page_align_down(pml1_addr[pml1]) + (virt_addr - page_align_down(virt_addr)));
            }
            pml2 = 0;
        }
        pml3 = 0;
    }
    return 0;
}

void write_vmem(page_t pml4_addr, uintptr_t virt_addr, char *data, size_t len) {
    while (len > 0) {
        // get the address of this virtual address in kernel memory
        uint64_t kernel_addr = virt_to_phys(pml4_addr, virt_addr);
        if (!kernel_addr) {
            kpanic("write_vmem: virtual address is not mapped! Address: %p\n"
                   "         Cannot write to vmem. Halting.\n", virt_addr);
        }
        kernel_addr += kernel.hhdm;
        uint64_t bytes_to_copy = (len < PAGE_SIZE) ? len : PAGE_SIZE;
        memcpy((char*) kernel_addr, data, bytes_to_copy);
        len -= bytes_to_copy;
        virt_addr += bytes_to_copy;
        data += bytes_to_copy;
    }
}

void read_vmem(page_t pml4_addr, uintptr_t virt_addr, char *buffer, size_t len) {
    while (len > 0) {
        // get the address of this virtual address in kernel memory
        uint64_t kernel_addr = virt_to_phys(pml4_addr, virt_addr);
        if (!kernel_addr) {
            kpanic("read_vmem: virtual address is not mapped! Address: %p\n"
                   "         Cannot read from vmem. Halting.\n", virt_addr);
        }
        kernel_addr += kernel.hhdm;
        uint64_t bytes_to_copy = (len < PAGE_SIZE) ? len : PAGE_SIZE;
        memcpy(buffer, (char*) kernel_addr, bytes_to_copy);
        len -= bytes_to_copy;
        virt_addr += bytes_to_copy;
        buffer += bytes_to_copy;
    }
}

extern uint8_t section_text_begin[];
extern uint8_t section_text_end[];

extern uint8_t section_const_data_begin[];
extern uint8_t section_const_data_end[];

extern uint8_t section_mut_data_begin[];
extern uint8_t section_mut_data_end[];

void map_all_memory(page_t pml4, bool verbose) {
    BootMemRegion region;
    for(size_t i = 0; i < boot_get_memregion_count(); ++i) {
        boot_get_memregion_at(&region, i);
        pageflags_t flags = KERNEL_PFLAG_PRESENT | KERNEL_PFLAG_WRITE | KERNEL_PFLAG_EXEC_DISABLE;
        switch(region.kind) {
        case BOOT_MEMREGION_FRAMEBUFFER:
            flags |= KERNEL_PFLAG_WRITE_COMBINE;
            FALLTHROUGH 
        case BOOT_MEMREGION_USABLE:
        case BOOT_MEMREGION_KERNEL_AND_MODULES:
        case BOOT_MEMREGION_BOOTLOADER_RECLAIMABLE:
        case BOOT_MEMREGION_ACPI_RECLAIMABLE: {
            paddr_t   phys = page_align_down(region.address);
            uintptr_t virt = page_align_down(region.address + kernel.hhdm);
            size_t   pages = region.size/PAGE_SIZE;
            if (verbose)
                kprint("%zu> mapping %p -> %p (%zu pages)\n", i, (void*)phys, (void*)virt, pages);
            if(!page_mmap(pml4, phys, virt, pages, flags)) {
                kpanic("Failed to map %zu of type %s. (%p -> %p) %zu pages", i, boot_memregion_kind_str(region.kind), phys, virt, pages);
            }
        } break;
        default:
        }
    }

}

void map_kernel(BootAddrPair addr_resp, page_t pml4) {
    uintptr_t phys, virt;
    size_t len;
    phys = page_align_down(addr_resp.phys + (((uintptr_t)section_text_begin) - addr_resp.virt));
    virt = page_align_down((uintptr_t)section_text_begin);
    len  = (page_align_up((uintptr_t)section_text_end) - page_align_down((uintptr_t)section_text_begin))/PAGE_SIZE;
    kprint("Mapping .text   (%p -> %p) %zu pages\n", (void*)phys, (void*)virt, len);
    if(!page_mmap(pml4, phys, virt, len, KERNEL_PFLAG_PRESENT)) {
        kpanic("Failed to map .text");
    }
    phys = page_align_down(addr_resp.phys + (((uintptr_t)section_const_data_begin) - addr_resp.virt));
    virt = page_align_down((uintptr_t)section_const_data_begin);
    len  = (page_align_up((uintptr_t)section_const_data_end) - page_align_down((uintptr_t)section_const_data_begin))/PAGE_SIZE;
    kprint("Mapping .rodata (%p -> %p) %zu pages\n", (void*)phys, (void*)virt, len);
    if(!page_mmap(pml4, phys, virt, len, KERNEL_PFLAG_PRESENT | KERNEL_PFLAG_EXEC_DISABLE)) {
        kpanic("Failed to map .rodata");
    }
    phys = page_align_down(addr_resp.phys + (((uintptr_t)section_mut_data_begin) - addr_resp.virt));
    virt = page_align_down((uintptr_t)section_mut_data_begin);
    len = (page_align_up((uintptr_t)section_mut_data_end) - page_align_down((uintptr_t)section_mut_data_begin))/PAGE_SIZE;
    kprint("Mapping .data   (%p -> %p) %zu pages\n", (void*)phys, (void*)virt, len);
    if(!page_mmap(pml4, phys, virt, len, KERNEL_PFLAG_PRESENT | KERNEL_PFLAG_WRITE | KERNEL_PFLAG_EXEC_DISABLE)) {
        kpanic("Failed to map .data");
    }
}

// NOTE: Mapping the actual executable is left to exec. This simply needs to initialise stuff.
status_t init_task_paging(page_t *new_pml4) {
    *new_pml4 = kernel_alloc_pages(1);
    memset((void*) *new_pml4, 0, PAGE_SIZE);
    map_all_memory(*new_pml4, false);
    return 0;
}

void init_paging() {
    BootAddrPair addr_resp = {0};
    kernel_bootpair(&addr_resp);
    kernel.pml4 = kernel_alloc_pages(1);
    if(!kernel.pml4) kpanic("ERROR: Could not allocate page map. Ran out of memory");
    memset(kernel.pml4, 0, PAGE_SIZE);
    map_all_memory(kernel.pml4, true);
    map_kernel(addr_resp, kernel.pml4);
    kprint("Allocating stack (%p) %zu pages\n", (void*)KERNEL_STACK_ADDR, (size_t)KERNEL_STACK_PAGES);
    if(!page_alloc(kernel.pml4, KERNEL_STACK_ADDR, KERNEL_STACK_PAGES, KERNEL_PFLAG_PRESENT | KERNEL_PFLAG_WRITE)) {
        kpanic("Failed to map/allocate the stack");
    }
    // NOTE: Kind of temporary. Might remove later if need be
    asm volatile(
        "movl $0x277, %%ecx;"
        "rdmsr;"
        "movw $0x0401, %%dx;"
        "wrmsr;"
        ::: "eax", "ecx", "edx", "memory"
    );
}
