/**
 * @defgroup   WD
 * Warpdrive
 * @{
 * @}
 */

#include "../include/config.h"
#include "wd_debug.h"
#include "wd_dev_emmc.h"
    #include "wd_dev_gpio.h"
    #include "../include/clock.h"
#include <stdint.h>
#include <stdint.h>

static uintmax_t wd_machine_id;
static uintptr_t wd_atags;

/**
 * Return if something bad happened otherwise chug on
 */
intmax_t 
#if BIT == 32
__attribute__((target("arm")))
#endif
    wd_main(uintmax_t r0 __attribute__((unused)), uintmax_t r1, uintmax_t r2) {
    // Disable IRQ and FIQ interrupts
#if BIT == 32
    __asm__ volatile("cpsid if");
#elif BITS == 64
    __asm__ volatile("msr daifset, #0xF");
#endif
    wd_machine_id = r1;
    wd_atags = (uintptr_t) r2;

#ifdef UART1_DEBUG_HARDWARE_OUT
    wd_dev_uart1_init_gpio();
#endif

#ifdef UART1_DEBUG
    wd_dev_uart1_init();
#endif

    WD_ASSERT_HARD(wd_dev_emmc_init() == WD_DEV_EMMC_ERRC_NONE);
    WD_INFO("Inited EMMC :)");

    while (1) {
        if (wd_dev_gpio_get(47))
            WD_INFO("Pluh\n");
        delay_cycles(15000000);
    }

    wd_panic:
    WD_INFO("PLUH\n");
    return 0xDEADBEEF;
}