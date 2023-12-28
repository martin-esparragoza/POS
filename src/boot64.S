/**
 * Get to C
 * 64 BIT
 */

// Origin set by linker
.extern __start
.extern __bss_start
.extern __bss_end
.extern wd_main

.section .text
    .global _pos_boot_start
    _pos_boot_start:
        // All processors are already halted for us on power up
        
        ldr x5, =__start
        mov sp, x5
        
        stp x0, x1, [sp, -16]!
        str x2, [sp, -16]!
        
        ldr w0, 0
        ldr x1, =__bss_start
        ldr x2, =__bss_end
        
        // Clear out bss and when done branch
        1:
            cmp x1, x2
            bhs 2f
            
            strb w0, [x1], #1
            b 1b
        2:
            ldr x2, [sp], 16
            ldr x1, [sp], 16
            ldr x0, [sp], 16
            mov lr, pos_boot_halt
            b wd_main
        
        // Return for error code :(
    
    pos_boot_halt:
        // On halt r0 should be equal to 0xDEADBEEF
        wfe
        b pos_boot_halt

.section .data
    .ascii "wd SIG 64 BIT CODE"
