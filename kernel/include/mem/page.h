#pragma once
#include <stdint.h>
// TODO: In the future here is where paging code will also go
#define PAGE_SIZE 4096
#define page_align_up(x)  (((x+(PAGE_SIZE-1))/PAGE_SIZE)*PAGE_SIZE)
#define bytes_to_pages(x) ((x+(PAGE_SIZE-1))/PAGE_SIZE)
typedef uint64_t paddr_t;

