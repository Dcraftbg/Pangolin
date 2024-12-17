#include <scheduler.h>
#include <kernel.h>
#include <memory.h>
#include <mem/page.h>
#include <string.h>
#include <vfs.h>
#include <kprint.h>
#include <exec.h>
#include <stddef.h>

status_t verify_elf(elf_file_header *file_header) {
    if (
        memcmp(file_header->id, "\x7f" "ELF", 4) || // It's not an elf file
        file_header->id[5] != 1 || // It's big endian but needs to be little endian
        file_header->id[4] != 2 || // It's a 32 bit ELF but needs to be 64 bit
        file_header->machine_type != 0x3E // It's not for x86_64
    ) {
        return -INVALID_KIND;
    }
    return 0;
}

// TODO: Add argv and envp
status_t execve(const char *filename) {
    status_t e;
    Inode *f;
    if ((e = vfs_open_abs(filename, &f)) < 0) {
        kprint("Failed to open file \"%s\" with status code %zu\n", filename, e);
        return e;
    }
    elf_file_header file_header;
    if ((e = inode_read(f, &file_header, 0, sizeof(elf_file_header)) - 1) < 0) {
        elf_read_err:
        kprint("Failed to read from file \"%s\" with status code %zu\n", filename, e);
        elf_generic_err:
        idrop(f);
        return e;
    }
    if ((e = verify_elf(&file_header)) < 0) {
        kprint("Invalid ELF file.\n");
        goto elf_generic_err;
    }
    Task *current_task = kernel.scheduler.current_task;
    off_t offset = file_header.program_header_offset;
    for (size_t i = 0; i < file_header.program_header_entry_count; i++) {
        elf_program_header program_header;
        if ((e = inode_read(f, &program_header, offset, sizeof(elf_file_header)) - 1) < 0)
            goto elf_read_err;
        if (program_header.type == 1) {
            paddr_t header_data_phys = kernel_alloc_phys_pages(bytes_to_pages(page_align_up(program_header.size_in_memory)));
            if ((e = inode_read(f, (void*) (header_data_phys + kernel.hhdm), program_header.offset, program_header.size_in_file)) < 0)
                goto elf_read_err;
            uint64_t flags = KERNEL_PFLAG_USER | KERNEL_PFLAG_PRESENT;
            if (!(program_header.flags & ELF_FLAG_WRITABLE))
                flags |= KERNEL_PFLAG_WRITE;
            if (!page_mmap(current_task->pml4, header_data_phys, program_header.virtual_address, bytes_to_pages(program_header.size_in_memory), flags)) {
                kprint("Couldn't map section into new user task.\n");
                e = -NOT_ENOUGH_MEMORY;
                goto elf_generic_err;
            }
            add_memregion(&current_task->memregion_list, program_header.virtual_address, program_header.size_in_memory, flags);
        }
        offset += file_header.program_header_entry_size;
    }
    if (!page_alloc(current_task->pml4, USER_STACK_ADDR, USER_STACK_PAGES, KERNEL_PFLAG_WRITE | KERNEL_PFLAG_USER | KERNEL_PFLAG_PRESENT)) {
        kprint("Couldn't allocate and map new user stack.\n");
        e = -NOT_ENOUGH_MEMORY;
        goto elf_generic_err;
    }
    add_memregion(&current_task->memregion_list, USER_STACK_ADDR, USER_STACK_PAGES, KERNEL_PFLAG_WRITE | KERNEL_PFLAG_USER | KERNEL_PFLAG_PRESENT);
    current_task->entry = (void*) file_header.entry;
    current_task->flags = TASK_FIRST_EXEC | TASK_PRESENT;
    idrop(f);
    return 0;
}
