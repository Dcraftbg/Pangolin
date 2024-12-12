#pragma once
#include <status.h>

typedef struct {
    char id[16];
    uint16_t type;
    uint16_t machine_type;
    uint32_t version;
    uint64_t entry;
    uint64_t program_header_offset;
    uint64_t section_header_offset;
    uint32_t flags;
    uint16_t header_size;
    uint16_t program_header_entry_size;
    uint16_t program_header_entry_count;
    uint16_t section_header_entry_size;
    uint16_t section_header_entry_count;
    uint16_t section_name_string_table_index;
} __attribute__((packed)) elf_file_header;

typedef struct {
    uint32_t type;
    uint32_t flags;
    uint64_t offset;
    uint64_t virtual_address;
    uint64_t rsvd;
    uint64_t size_in_file;
    uint64_t size_in_memory;
    uint64_t align;
} __attribute__((packed)) elf_program_header;

status_t execve(const char *filename);
