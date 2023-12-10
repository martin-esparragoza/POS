ENTRY(_pos_boot_start); /* Covers annoyingness */

SECTIONS {
    . = 0x8000;
    __start = .;
    .text 0x8000 : {
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
    
    /* standard library should NOT be defined in the warp drive */
    /* standard library should be loaded in before adding the kernel process to the process map (dll) */
    /* a very crude interfacing library will be used for things such as filesystem io, printing, and process creation */
}