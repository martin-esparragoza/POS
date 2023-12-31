#include "wd_dev_emmc.h"
#include "wd_dev_mbox_propint.h"
#include "wd_dev_gpio.h"
#include <stdint.h>

static const char * errc_to_string[]= {
    [WD_DEV_EMMC_ERRC_NONE] =           "There was no error",
    [WD_DEV_EMMC_ERRC_FAIL_NO_CLOCK] =  "There is no EMMC clock",
    [WD_DEV_EMMC_ERRC_FAIL_SET_CLOCK] = "Failed to set clock to a rate of 100MHz"
};

static uint32_t clockrate = 100000000; // Desired, not guaranteed

inline const char * wd_dev_emmc_errctostr(enum wd_dev_emmc_errc errc) {
    return errc_to_string[errc];
}

enum wd_dev_emmc_errc wd_dev_emmc_init() {
    // Turn on the EMMC clock
    volatile struct wd_dev_mbox_propint_buffer * buffer = __builtin_alloca_with_align(128, 128);
    wd_dev_mbox_propint_buffer_new(buffer);

    uint32_t valueon[] = {1 /* emmc clock */, 1 /* set clock to on */};
    wd_dev_mbox_propint_buffer_addtag(buffer, 0x00038001 /* set clock state */, valueon, sizeof(valueon));

    uint32_t valueset[] = {1 /* emmc clock */, clockrate, 0 /* skip setting turbo does not matter */};
    wd_dev_mbox_propint_buffer_addtag(buffer, 0x00038002 /* set clock rate */, valueset, sizeof(valueset));
    wd_dev_mbox_propint_buffer_addendtag(buffer);

    wd_dev_mbox_propint_buffer_send(buffer);

    volatile struct wd_dev_mbox_propint_tag * tag = wd_dev_mbox_propint_buffer_gettag(buffer, 0);

    if (wd_dev_mbox_propint_buffer_getcode(buffer) != WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQS || // FIXME: Hopefully not that bad
        !wd_dev_mbox_propint_tag_issuccessful(tag) ||
        ((volatile uint32_t *) wd_dev_mbox_propint_tag_getvalue(tag))[1] & 0x02 /* the clock does not exist */) {

        return WD_DEV_EMMC_ERRC_FAIL_NO_CLOCK;
    }

    tag = wd_dev_mbox_propint_buffer_gettag(buffer, 1);

    clockrate = ((volatile uint32_t *) wd_dev_mbox_propint_tag_getvalue(tag))[1];

    if (!wd_dev_mbox_propint_tag_issuccessful(tag) || clockrate == 0)
        return WD_DEV_EMMC_ERRC_FAIL_SET_CLOCK;

    // Now set GPIO pins (attrociously done but whatever)
    wd_dev_gpio_setpinfunction(47, WD_DEV_GPIO_FUN_INPUT); // GPIO_CD
    wd_dev_gpio_setpinfunction(48, WD_DEV_GPIO_FUN_ALT3);  // GPIO_CLK
    wd_dev_gpio_setpinfunction(49, WD_DEV_GPIO_FUN_ALT3);  // GPIO_CMD
    wd_dev_gpio_setpinfunction(50, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT0
    wd_dev_gpio_setpinfunction(51, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT1
    wd_dev_gpio_setpinfunction(52, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT2
    wd_dev_gpio_setpinfunction(53, WD_DEV_GPIO_FUN_ALT3);  // GPIO_DAT3

    unsigned char pins[] = {47, 48, 49, 50, 51, 52};
    wd_dev_gpio_setpupd_multi(pins, sizeof(pins) / sizeof(pins[0]), WD_DEV_GPIO_PUPD_UP);

    return WD_DEV_EMMC_ERRC_NONE;
}