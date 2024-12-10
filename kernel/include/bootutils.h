#pragma once
#include <stddef.h>
#include <mem/page.h>
enum {
    BOOT_MEMREGION_USABLE,
    BOOT_MEMREGION_RESERVED,
    BOOT_MEMREGION_ACPI_RECLAIMABLE,
    BOOT_MEMREGION_ACPI_NVS,
    BOOT_MEMREGION_BAD_MEMORY,
    BOOT_MEMREGION_BOOTLOADER_RECLAIMABLE,
    BOOT_MEMREGION_KERNEL_AND_MODULES,
    BOOT_MEMREGION_FRAMEBUFFER,
    BOOT_MEMREGION_TYPE_COUNT
};

typedef struct {
    bool is_valid;
    void *addr;
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint64_t bytes_per_pix;
} Framebuffer;

const char* boot_memregion_kind_str(uint32_t kind);
typedef struct {
    uint32_t kind;
    paddr_t address;
    // In bytes. Not in pages
    size_t size;
} BootMemRegion;
size_t boot_get_memregion_count();
void   boot_get_memregion_at(BootMemRegion* region, size_t index);
#define BOOT_HHDM_SIZE (4LL*1024LL*1024LL*1024LL)
uintptr_t boot_get_hhdm();
typedef struct {
    paddr_t   phys;
    uintptr_t virt;
} BootAddrPair;

void kernel_bootpair(BootAddrPair* pair);
Framebuffer boot_get_framebuffer();
void* boot_get_initrd();
