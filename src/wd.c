/**
 * @defgroup   WD
 * Warpdrive
 * @{
 * @}
 */

#include <stdint.h>
#include "wd_mem.h"
#include "wd_dev_uart1.h"
#include "wd_dev_gpio.h"
#include "wd_stdio.h"
#include "wd_time.h"

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

    pos_wd_dev_uart1_init();

    /*char string[] = "Mama mia!\n";
    pos_wd_dev_uart1_write_data((uint8_t *) string, sizeof(string) / sizeof(string[0]));

    pos_wd_fprintf(&pos_wd_dev_uart1_write_char, "Dead beef! %d\n", 1245);

    pos_wd_dev_uart1_write_data((uint8_t *) string, sizeof(string) / sizeof(string[0]));

    pos_wd_fprintf(&pos_wd_dev_uart1_write_char, "mama\n");

    pos_wd_dev_uart1_printf("Mama mia: %d\n", 0xDEADBEEF);*/

    while (1) {
        pos_wd_dev_uart1_write_char('a');
    }

    //pos_wd_dev_gpio_setpupd(14, POS_WD_DEV_GPIO_PUPD_DOWN);
    //pos_wd_dev_gpio_setpinfunction(14, POS_WD_DEV_GPIO_FUN_OUTPUT);
    //pos_wd_dev_gpio_set(14, POS_WD_DEV_GPIO_STATE_HIGH);

    return POS_WD_SUCCESS;
}