/* Only difference between linker32 and 64 is the origin (FOR NOW)

ENTRY(_pos_boot_start); /* Covers annoyingness */

SECTIONS {
    . = 0x80000;
    __start = .;
    .text 0x80000 : {
        __text_start = .;
        *( .text );
        __text_end = .;
    }
    
    .rodata : {
        __rodata_start = .;
        *( .rodata );
        __rodata_end = .;
    }
    
    .data : {
        __data_start = .;
        *( .data );
        __data_end = .;
    }
    
    .bss : {
        __bss_start = .;
        *( .bss );
        __bss_end = .;
    }
    
    /* a very crude interfacing library will be used for things such as filesystem io, printing, and process creation */
}