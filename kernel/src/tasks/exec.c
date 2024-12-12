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
        idrop(f);
        return e;
    }
    if ((e = verify_elf(&file_header)) < 0) {
        kprint("Invalid ELF file.\n");
        idrop(f);
        return e;
    }
    off_t offset = file_header.program_header_offset;
    for (size_t i = 0; i < file_header.program_header_entry_count; i++) {
        elf_program_header program_header;
        if ((e = inode_read(f, &program_header, offset, sizeof(elf_file_header)) - 1) < 0)
            goto elf_read_err;
        if (program_header.type == 1) {
            kprint("Found loadable section of offset %zu, size in file %zu, vaddr %p\n",
                    program_header.offset, program_header.size_in_file, (void*) program_header.virtual_address);
        }

        offset += file_header.program_header_entry_size;
    }
    idrop(f);
    return 0;
}
