/**
 * Get to C
 * 32 BIT
 */

// Origin set by linker
.syntax unified
.code 32
.extern __start
.extern __bss_start
.extern __bss_end
.extern pos_wd_main

.section .text
    .global _pos_boot_start
    _pos_boot_start:
        // Stop all coprocessors (haven't dealth with coprocessors yet so this code is shamefully stolen)
        mrc p15, 0, r5, c0, c0, 5
        and r5, r5, 3
        cmp r5, 0
        ldrne r0, =0xDEADBEEF
        bne pos_boot_halt // TODO: process error so we dont die
        
        ldr sp, =__start
        
        push {r0-r2}
        
        // r0 = 0
        ldr r1, =__bss_start
        ldr r2, =__bss_end
        
        // Clear out bss and when done branch
        1:
            cmp r1, r2
            pophs {r0-r2}
            // Ticking time bomb :) (maybe)
            movhs lr, pos_boot_halt
            bhs pos_wd_main
            
            strb r0, [r1], 1
            b 1b
        
        // Return for error code :(
    
    pos_boot_halt:
        // On halt r0 should be equal to 0xDEADBEEF
        wfe
        b pos_boot_halt

.section .data
    .ascii "POS_WD SIG 32 BIT CODE"
