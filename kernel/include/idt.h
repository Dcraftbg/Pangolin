#pragma once
#include <stdint.h>

typedef struct {
    uint16_t offset1;
    uint16_t segment_selector;
    uint8_t rsvd;
    uint8_t flags;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t reserved;
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) IDTR;

void init_IDT();
