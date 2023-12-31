#include "wd_dev_uart1.h"
#include "wd_dev.h"
#include "wd_dev_gpio.h"
#include "wd_dev_mbox_propint.h"
#include "wd_dev_timer.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Random reg &s are to clobber registers in a jank way

bool wd_dev_uart1_init() {
    // Initialize the UART1 (mini uart)
    wd_dev_uart1_enable();
    WD_DEV_UART1_AUX_MU_CNTL_REG = 0; // Disable stuff like auto folow control
    WD_DEV_UART1_AUX_MU_IER_REG = 0; // Disable interrupts
    wd_dev_uart1_enable_sevenbit();
    if (!wd_dev_uart1_setbaud(115200))
        return false;
    wd_dev_uart1_enable_transmitter();

    return true;
}

void wd_dev_uart1_init_gpio() {
    wd_dev_gpio_setpupd(14, WD_DEV_GPIO_PUPD_DOWN);
    wd_dev_gpio_setpupd(15, WD_DEV_GPIO_PUPD_DOWN);
    wd_dev_gpio_setpinfunction(14, WD_DEV_GPIO_FUN_ALT5); // Transfer line
    wd_dev_gpio_setpinfunction(15, WD_DEV_GPIO_FUN_ALT5); // Recieve line
}

void wd_dev_uart1_set_enabled(bool enabled) {
    uint32_t savebits = WD_DEV_GEN_AUX_ENABLES & 6;
    WD_DEV_GEN_AUX_ENABLES = savebits | enabled;
}

bool wd_dev_uart1_setbaud(unsigned baud) {
    // Get clock rate
    volatile struct wd_dev_mbox_propint_buffer * buffer = __builtin_alloca_with_align(64, 128);
    wd_dev_mbox_propint_buffer_new(buffer);
    uint32_t value[] = {4 /* clock id of core */, 0 /* placeholder for returned rate */};
    wd_dev_mbox_propint_buffer_addtag(buffer, 0x00030002 /* get clock rate */, value, sizeof(value));
    wd_dev_mbox_propint_buffer_addendtag(buffer);

    if (!wd_dev_mbox_propint_buffer_send(buffer, 10000))
        return false;

    volatile struct wd_dev_mbox_propint_tag * tag = wd_dev_mbox_propint_buffer_gettag(buffer, 0);
    if (wd_dev_mbox_propint_buffer_getcode(buffer) != WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQS ||
       tag == NULL ||
       !wd_dev_mbox_propint_tag_issuccessful(tag))
        return false;

    uint32_t reg = (((uint32_t *) wd_dev_mbox_propint_tag_getvalue(tag))[1] / (8 * baud)) - 1;
    if (reg > 0xFFFF) {
        return false;
    }

    WD_DEV_UART1_AUX_MU_BAUD_REG = reg;
    return true;
}

void wd_dev_uart1_write_char(char data) {
    if (data == '\0') // UART1 can't send a 0 bc no parity
        return;

    // Wait until we can send
    // No errc because its really not the end of the world if this fails
    WD_DEV_TIMER_WAITUNTILCONDITION((WD_DEV_UART1_AUX_MU_LSR_REG & 0x20), {return;}, 500);
    WD_DEV_UART1_AUX_MU_IO_REG = data;
}

void wd_dev_uart1_write_data(uint8_t * data, size_t length) {
    size_t i = 0;
    while (i < length) {
        wd_dev_uart1_write_char(data[i++]);
    }
}

void wd_dev_uart1_set_reciever(bool recieve) {
    uint32_t savebits = WD_DEV_UART1_AUX_MU_CNTL_REG & 0xFE;
    WD_DEV_UART1_AUX_MU_CNTL_REG = savebits | recieve;
}

void wd_dev_uart1_set_transmitter(bool transmit) {
    uint32_t savebits = WD_DEV_UART1_AUX_MU_CNTL_REG & 0xFD;
    WD_DEV_UART1_AUX_MU_CNTL_REG = savebits | (transmit << 1);
}

void wd_dev_uart1_set_bit(bool sevenbit) {
    uint32_t savebits = WD_DEV_UART1_AUX_MU_LCR_REG & 0xFE;
    WD_DEV_UART1_AUX_MU_LCR_REG = savebits | sevenbit;
}