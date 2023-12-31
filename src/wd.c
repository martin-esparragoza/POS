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
#include "wd_dev_timer.h"
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
    WD_ASSERT_SOFT(wd_dev_uart1_init(), {});
#endif

    WD_INFO("UART Init took %d microseconds\n", wd_dev_timer_currenttimeus());

    enum wd_dev_emmc_errc errc = wd_dev_emmc_init();
    WD_ASSERT_HARD(errc == WD_DEV_EMMC_ERRC_NONE, {WD_INFO("Error string: %s\n", wd_dev_emmc_errctostr(errc));});
    WD_INFO("Inited EMMC :)\n");

    WD_INFO("Total bootloader time: %d microseconds\n", wd_dev_timer_currenttimeus());

    wd_panic:
    return 0xDEADBEEF;
}