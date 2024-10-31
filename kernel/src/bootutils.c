#include <bootutils.h>
#include <kpanic.h>

static const char* boot_memregion_kind_map[BOOT_MEMREGION_TYPE_COUNT] = {
    [BOOT_MEMREGION_USABLE]                 = "Usable",
    [BOOT_MEMREGION_RESERVED]               = "Reserved",
    [BOOT_MEMREGION_ACPI_RECLAIMABLE]       = "Acpi Reclaimable",
    [BOOT_MEMREGION_ACPI_NVS]               = "Acpi NVS",
    [BOOT_MEMREGION_BAD_MEMORY]             = "Bad Memory",
    [BOOT_MEMREGION_BOOTLOADER_RECLAIMABLE] = "Bootloader Reclaimable",
    [BOOT_MEMREGION_KERNEL_AND_MODULES]     = "Kernel And Modules",
    [BOOT_MEMREGION_FRAMEBUFFER]            = "Framebuffer",
};
const char* boot_memregion_kind_str(uint32_t kind) {
    if(kind >= (sizeof(boot_memregion_kind_map)/sizeof(*boot_memregion_kind_map))) return NULL;
    return boot_memregion_kind_map[kind];
}

#include <limine.h>
static volatile struct limine_memmap_request limine_memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0 
};
static volatile struct limine_hhdm_request limine_hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};
size_t boot_get_memregion_count() {
    if(limine_memmap_request.response) return limine_memmap_request.response->entry_count;
    return 0;
}
// NOTE: Assumes the type field is the same as the bootutils memory region type.
// Which it should be as limine is the primary bootloader anyway
static void memregion_from_limine(BootMemRegion* region, struct limine_memmap_entry* entry) {
    region->address = entry->base;
    region->size = entry->length;
    region->kind = entry->type;
}
void boot_get_memregion_at(BootMemRegion* region, size_t index) {
    memregion_from_limine(region, limine_memmap_request.response->entries[index]);
}
uintptr_t boot_get_hhdm() {
    if(!limine_hhdm_request.response) kpanic("(boot:limine) Missing hhdm response");
    return limine_hhdm_request.response->offset;
}