#pragma once
// NOTE: Inspired by paging from a project of mine (Dcraftbg) MinOS: https://github.com/Dcraftbg/MinOS/blob/master/kernel/src/page.h 
// Licensed under MIT
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <status.h>
// TODO: In the future here is where paging code will also go
#define PAGE_SIZE 4096
#define KERNEL_PAGE_ENTRIES 512
#define page_align_up(x)   ((((x)+(PAGE_SIZE-1))/PAGE_SIZE)*PAGE_SIZE)
#define page_align_down(x) (((x)/PAGE_SIZE)*PAGE_SIZE)
#define bytes_to_pages(x)  (((x)+(PAGE_SIZE-1))/PAGE_SIZE)
typedef uint64_t paddr_t;
typedef uint64_t *page_t;
typedef uint64_t pageflags_t;

#define KERNEL_STACK_PAGES 10LL
#define KERNEL_STACK_ADDR (-(KERNEL_STACK_PAGES*PAGE_SIZE))
#define KERNEL_STACK_PTR 0xFFFFFFFFFFFFF000LL

#define USER_STACK_PAGES 2
#define USER_STACK_ADDR  (USER_STACK_PTR - USER_STACK_PAGES*PAGE_SIZE)
#define USER_STACK_PTR   0x700000000000

#define KERNEL_PFLAG_PRESENT       0b1
#define KERNEL_PFLAG_WRITE         0b10
#define KERNEL_PFLAG_USER          0b100
#define KERNEL_PFLAG_WRITE_THROUGH 0b1000
#define KERNEL_PFLAG_CACHE_DISABLE 0b10000
#define KERNEL_PFLAG_WRITE_COMBINE 0b10000000
#define KERNEL_PFLAG_EXEC_DISABLE  0// 0b1000000000000000000000000000000000000000000000000000000000000000
// NOTE: Dirty
#define KERNEL_PFLAG_ACCESSED      0b100000

#define KERNEL_PFLAGS_MASK 0x8000000000000FFFLL
// Technically incorrect but idrk
#define KERNEL_PADDR_MASK  0x7FFFFFFFFFFFF000LL

bool page_mmap(page_t pml4_addr, uintptr_t phys, uintptr_t virt, size_t pages_count, pageflags_t flags);
bool page_alloc(page_t pml4_addr, uintptr_t virt, size_t pages_count, pageflags_t flags);
void init_paging(); // Called to initialse
status_t init_task_paging(page_t *new_pml4);
paddr_t virt_to_phys(page_t pml4_addr, uint64_t virt_addr);
void write_vmem(page_t pml4_addr, uintptr_t virt_addr, char *data, size_t len);
void read_vmem(page_t pml4_addr, uintptr_t virt_addr, char *buffer, size_t len);

#define kernel_switch_vtable() \
    do {\
        __asm__ volatile (\
           "movq %0, %%cr3\n"\
           "movq %1, %%rsp\n"\
           "movq $0, %%rbp\n"\
           :\
           : "r" ((uintptr_t)kernel.pml4 - kernel.hhdm), \
             "r" (KERNEL_STACK_PTR)\
        ); \
        kprint("Switched page tree.\n");\
    } while (0)
