/**
 * @defgroup   WD
 * Warpdrive
 * @{
 * @}
 */

#include <stdint.h>
#include "wd_mem.h"
#include "wd_dev_uart1.h"

#define POS_WD_ERROR   0xBEEFDEAD
#define POS_WD_SUCCESS 0xDEADBEEF

static uint32_t pos_wd_machine_id;
static void * pos_wd_atags;

/**
 * Return if something bad happened otherwise chug on
 * NOTE: This calling convention is for aapcs
 */
int32_t __attribute__((target("arm"))) pos_wd_main(uint32_t r0 __attribute__((unused)), uint32_t r1, uint32_t r2) {
    asm volatile("cpsid if"); // Disable IRQ and FIQ interrupts
    pos_wd_machine_id = r1;
    pos_wd_atags = (void *) r2;
    
    // Initialize the UART1 (mini uart)
    pos_wd_dev_uart1_enable();
    pos_wd_dev_uart1_enable_transmitter();
    pos_wd_dev_uart1_enable_sevenbit();
    pos_wd_dev_uart1_enable_rts();
    if (!pos_wd_dev_uart1_set_baud(115200))
        return POS_WD_ERROR;

    char string[] = "Mama mia!";
    pos_wd_dev_uart1_write_sync((uint8_t *) string, sizeof(string) / sizeof(string[0]));

    return POS_WD_SUCCESS;
}