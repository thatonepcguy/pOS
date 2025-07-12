ENTRY(_start)

SECTIONS {
    . = 0x40100000;
    .text : ALIGN(4) {
        __kernel = .;
        __text = .;
        KEEP(*(.text.boot));
        *(.text .text.*)
        *(.text.vectors .text.vectors.*)
        __text_end = .;
    }

    .rodata : ALIGN(4) {
        __rodata = .;
        *(.rodata .rodata.*)
        __rodata_end = .;
    }

    .data : ALIGN(4) {
        __data = .;
        *(.data .data.*)
        __data_end = .;
    }
    
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.*)
        __bss_end = .;
    }

    .stack : ALIGN(16) {
        __stack = .;
        . += 128 * 1024; /* 128 KiB */ 
        __stack_top = .;
    }

    .heap : ALIGN(8) {
        __heap = .;
        . += 16*1024*1024; /* 16 MB*/
        __heap_end = .;
    }
}