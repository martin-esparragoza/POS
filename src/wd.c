/**
 * @defgroup   WD
 * Warpdrive
 * @{
 * @}
 */

#include <stdint.h>
#include "wd_mem.h"
#include "wd_dev_uart1.h"
#include "wd_stdio.h"

#define POS_WD_ERROR   0xBEEFDEAD
#define POS_WD_SUCCESS 0xDEADBEEF

static uintmax_t pos_wd_machine_id;
static uintptr_t pos_wd_atags;

/**
 * Return if something bad happened otherwise chug on
 * NOTE: This calling convention is for aapcs
 */
intmax_t 
#if BITS == 32
__attribute__((target("arm")))
#endif
         pos_wd_main(uintmax_t r0 __attribute__((unused)), uintmax_t r1, uintmax_t r2) {
    // Disable IRQ and FIQ interrupts
#if BITS == 32
    __asm__ volatile("cpsid if");
#elif BITS == 64
    __asm__ volatile("msr daifset, #0xF");
#endif
    pos_wd_machine_id = r1;
    pos_wd_atags = (uintptr_t) r2;
    
    // Initialize the UART1 (mini uart)
    pos_wd_dev_uart1_enable();
    pos_wd_dev_uart1_enable_transmitter();
    pos_wd_dev_uart1_enable_sevenbit();
    pos_wd_dev_uart1_enable_rts();
    if (!pos_wd_dev_uart1_set_baud(115200))
        return POS_WD_ERROR;

    char string[] = "Mama mia!\n";
    pos_wd_dev_uart1_write_data((uint8_t *) string, sizeof(string) / sizeof(string[0]));

    return POS_WD_SUCCESS;
}