#include <kprint.h>
#include <cpu/gdt.h>
#include <memory.h>
#include <kernel.h>

static uint64_t create_gdt_entry(uint64_t base, uint64_t limit, uint64_t access, uint64_t flags) {
    uint64_t base1  = base & 0xFFFF;
    uint64_t base2  = (base >> 16) & 0xFF;
    uint64_t base3  = (base >> 24) & 0xFF;
    uint64_t limit1 = limit & 0xFFFF;
    uint64_t limit2 = limit >> 16;
    uint64_t entry  = 0;
    entry |= limit1;
    entry |= limit2 << 48;
    entry |= base1  << 16;
    entry |= base2  << 32;
    entry |= base3  << 56;
    entry |= access << 40;
    entry |= flags  << 52;
    return entry;
}

static void create_system_segment_descriptor(uint64_t *GDT, uint8_t idx, uint64_t base, uint64_t limit, uint64_t access, uint64_t flags) {
    uint64_t limit1 = limit & 0xFFFF;
    uint64_t  limit2 = (limit >> 16) & 0b1111;
    uint64_t base1  = base & 0xFFFF;
    uint64_t  base2  = (base >> 16) & 0xFF;
    uint64_t  base3  = (base >> 24) & 0xFF;
    uint64_t base4  = (base >> 32) & 0xFFFFFFFF;
    GDT[idx] = 0;
    GDT[idx] |= limit1;
    GDT[idx] |= base1 << 16;
    GDT[idx] |= base2 << 32;
    GDT[idx] |= access << 40;
    GDT[idx] |= (limit2 & 0xF) << 48;
    GDT[idx] |= (flags & 0xF) << 52;
    GDT[idx] |= base3 << 56;
    GDT[idx + 1] = base4;
}

extern void reload_gdt();

__attribute__((noinline))
void init_GDT() {
    kernel.GDT = (uint64_t*) (kernel_alloc_phys_page() + kernel.hhdm);
    kernel.GDT[0] = create_gdt_entry(0, 0, 0, 0); // null
    kernel.GDT[1] = create_gdt_entry(0, 0, 0x9A, 0x2); // kernel code
    kernel.GDT[2] = create_gdt_entry(0, 0, 0x92, 0); // kernel data
    kernel.GDT[3] = create_gdt_entry(0, 0, 0xFA, 0x2); // user code
    kernel.GDT[4] = create_gdt_entry(0, 0, 0xF2, 0); // user data
    GDTR gdtr = (GDTR) {
        .size = (sizeof(uint64_t) * 5) - 1,
        .offset = (uint64_t) kernel.GDT
    };
    asm volatile("lgdt (%0)" : : "r" (&gdtr));
    reload_gdt();
}
