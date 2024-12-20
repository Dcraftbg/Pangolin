#include <bootutils.h>
#include <limine.h>
#include <kpanic.h>
#include <kprint.h>

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
static struct limine_internal_module initrd = {
    .path = "initrd",
    .flags = LIMINE_INTERNAL_MODULE_REQUIRED
};
struct limine_internal_module *module_list = &initrd;
static volatile struct limine_module_request initrd_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0,
    .internal_modules = &module_list,
    .internal_module_count = 1
};
static volatile struct limine_memmap_request limine_memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0 
};
static volatile struct limine_hhdm_request limine_hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};
static volatile struct limine_kernel_address_request limine_kernel_address_request = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0, 
};
static volatile struct limine_framebuffer_request limine_framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0, 
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
    if(!limine_memmap_request.response || limine_memmap_request.response->entry_count <= index) kpanic("(boot:limine) Trying to get memmap entry at %zu. Out of bounds", index);
    memregion_from_limine(region, limine_memmap_request.response->entries[index]);
}
uintptr_t boot_get_hhdm() {
    if(!limine_hhdm_request.response) kpanic("(boot:limine) Missing hhdm response");
    return limine_hhdm_request.response->offset;
}
void* boot_get_initrd() {
    if(!initrd_request.response) {
        kprint("WARN: (boot:limine) Did not recieve initial ramdisk response from bootloader.\n");
        return NULL;
    }
    struct limine_file *modules = *(initrd_request.response->modules);
    if (initrd_request.response->module_count < 1) {
        kprint("WARN: (boot:limine) Less than one module provided by bootloader, could not get initial ramdisk.\n");
        return NULL;
    }
    return modules->address;
}
Framebuffer boot_get_framebuffer() {
    if(!limine_framebuffer_request.response) {
        kprint("(boot:limine) Missing framebuffer response. Outputting through serial only.");
        return (Framebuffer) {0};
    }
    return (Framebuffer) {
        .is_valid      = true,
        .addr          = (*limine_framebuffer_request.response->framebuffers)->address,
        .width         = (*limine_framebuffer_request.response->framebuffers)->width,
        .height        = (*limine_framebuffer_request.response->framebuffers)->height,
        .pitch         = (*limine_framebuffer_request.response->framebuffers)->pitch,
        .bytes_per_pix = (*limine_framebuffer_request.response->framebuffers)->bpp / 8,
    };
}

void kernel_bootpair(BootAddrPair* pair) {
    if(!limine_kernel_address_request.response) kpanic("(boot:limine) Missing kernel address response");
    pair->phys = limine_kernel_address_request.response->physical_base;
    pair->virt = limine_kernel_address_request.response->virtual_base;
}
