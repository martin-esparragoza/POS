#include "wd_dev_emmc.h"
#include "wd_dev_mbox_propint.h"
#include "wd_dev_gpio.h"
    #include "wd_dev_uart1.h"
    #include "../include/clock.h"
    #include "wd_debug.h"

static const char * errc_to_string[]= {
    [WD_DEV_EMMC_ERRC_NONE] =  "There was no error",
    [WD_DEV_EMMC_ERRC_FAIL_CLOCK] = "Failed to set clock for EMMC to 50 or 100 MHz"
};

inline const char * wd_dev_emmc_errctostr(enum wd_dev_emmc_errc errc) {
    return errc_to_string[errc];
}

enum wd_dev_emmc_errc wd_dev_emmc_init() {
    // Turn on the EMMC clock
    volatile struct wd_dev_mbox_propint_buffer * buffer = __builtin_alloca_with_align(64, 128);

    // Progressiveley decrease the MHz so it can be set
    wd_dev_mbox_propint_buffer_new(buffer);
    uint32_t value[] = {1 /* emmc clock */, 1 /* set clock to on */};
    wd_dev_mbox_propint_buffer_addtag(buffer, 0x00038001 /* set clock state */, value, sizeof(value));
    wd_dev_mbox_propint_buffer_addendtag(buffer);

    for (unsigned i = 0; i < buffer->size / 4; i++) {
        wd_dev_uart1_printf("0x%x ", ((volatile uint32_t *) buffer)[i]);
    }
    wd_dev_uart1_printf("\n");

    wd_dev_mbox_propint_buffer_send(buffer);
    delay_cycles(50000000);

    for (unsigned i = 0; i < buffer->size / 4; i++) {
        wd_dev_uart1_printf("0x%x ", ((volatile uint32_t *) buffer)[i]);
    }
    wd_dev_uart1_printf("\n");

    if (wd_dev_mbox_propint_buffer_getcode(buffer) != WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQS ||
        !wd_dev_mbox_propint_tag_issuccessful(wd_dev_mbox_propint_buffer_gettag(buffer, 0))) {

        return WD_DEV_EMMC_ERRC_FAIL_CLOCK;
    }

    // Now set GPIO pins (attrociously slow but whatever)

    wd_dev_gpio_setpinfunction(47, WD_DEV_GPIO_FUN_INPUT); // GPIO_CD
    wd_dev_gpio_setpinfunction(48, WD_DEV_GPIO_FUN_ALT3);  // GPIO_CLK
    wd_dev_gpio_setpinfunction(49, WD_DEV_GPIO_FUN_ALT3);  // GPIO_CMD
    wd_dev_gpio_setpinfunction(50, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT0
    wd_dev_gpio_setpinfunction(51, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT1
    wd_dev_gpio_setpinfunction(52, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT2
    wd_dev_gpio_setpinfunction(53, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT3
    WD_INFO("Set pin functions!\n");

    WD_INFO("Before PUPD\n");
    char pins[] = {47, 48, 49, 50, 51, 52};
    wd_dev_gpio_setpupd_multi(pins, 4, WD_DEV_GPIO_PUPD_UP);
    WD_INFO("Set pull up / down!\n");

    return WD_DEV_EMMC_ERRC_NONE;
}