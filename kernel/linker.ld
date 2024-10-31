OUTPUT_FORMAT(elf64-x86-64)

ENTRY(_start)

PHDRS
{
    requests PT_LOAD;
    text     PT_LOAD;
    rodata   PT_LOAD;
    data     PT_LOAD;
}

SECTIONS
{
    . = 0xffffffff80000000;

    .requests : {
        KEEP(*(.requests_start_marker))
        KEEP(*(.requests))
        KEEP(*(.requests_end_marker))
    } :requests

    . = ALIGN(CONSTANT(MAXPAGESIZE));
    section_text_begin = .;
    .text : {
        *(.text .text.*)
    } :text
    section_text_end = .;

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    section_const_data_begin = .;
    .rodata : {
        *(.rodata .rodata.*)
    } :rodata
    section_const_data_end = .;

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    section_mut_data_begin = .;
    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data
    section_mut_data_end = .;

    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }
}
