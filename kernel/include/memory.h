#pragma once
#include <stdint.h>
#include <stddef.h>
#include <mem/page.h>
paddr_t kernel_alloc_phys_page();
void  kernel_dealloc_phys_page(paddr_t page);
paddr_t kernel_alloc_phys_pages(size_t pages);
void  kernel_dealloc_phys_pages(paddr_t start, size_t pages);

void*  kernel_alloc_pages(size_t pages);
void kernel_dealloc_pages(void* addr, size_t pages);

#define kernel_alloc(x)             kernel_alloc_pages(bytes_to_pages(x))
#define kernel_dealloc(addr, bytes) kernel_dealloc_pages(addr, bytes_to_pages(x))

void init_mem();
