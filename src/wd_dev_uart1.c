#include "wd_dev_uart1.h"
#include "wd_time.h"
#include "wd_dev_gen.h"
#include "wd_dev_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Random reg &s are to clobber registers in a jank way

void pos_wd_dev_uart1_init() {
    pos_wd_dev_gpio_setpupd(14, POS_WD_DEV_GPIO_PUPD_DOWN);
    pos_wd_dev_gpio_setpupd(15, POS_WD_DEV_GPIO_PUPD_DOWN);
    pos_wd_dev_gpio_setpinfunction(14, POS_WD_DEV_GPIO_FUN_ALT5); // Transfer line
    pos_wd_dev_gpio_setpinfunction(15, POS_WD_DEV_GPIO_FUN_ALT5); // Recieve line
    //pos_wd_dev_gpio_clr(14);
    //pos_wd_dev_gpio_clr(15);
    
    // Initialize the UART1 (mini uart)
    pos_wd_dev_uart1_enable();
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG = 0; // Disable stuff like auto folow control
    POS_WD_DEV_UART1_AUX_MU_IER_REG = 0; // Disable interrupts
    pos_wd_dev_uart1_enable_sevenbit();
    pos_wd_dev_uart1_set_baud(115200);
    pos_wd_dev_uart1_enable_transmitter();
}

void pos_wd_dev_uart1_set_enabled(bool enabled) {
    uint32_t savebits = POS_WD_DEV_GEN_AUX_ENABLES & 6;
    POS_WD_DEV_GEN_AUX_ENABLES = savebits | enabled;
}

bool pos_wd_dev_uart1_set_baud(unsigned baud) {
    unsigned reg = (250000000 / (8 * baud)) - 1;
    if (reg > 0xFFFF)
        return false;

    POS_WD_DEV_UART1_AUX_MU_BAUD_REG = reg;
    return true;
}

void __attribute__((noinline)) pos_wd_dev_uart1_write_char(char data) {
    if (data == '\0') // UART1 can't send a 0 bc no parity
        return;

    while ((POS_WD_DEV_UART1_AUX_MU_LSR_REG & (0x20 | 0x40)) != (0x20 | 0x40)) {;}
    POS_WD_DEV_UART1_AUX_MU_IO_REG = data;
}

void pos_wd_dev_uart1_write_data(uint8_t * data, size_t length) {
    unsigned i = 0;
    while (i < length) {
        pos_wd_dev_uart1_write_char(data[i++]);
    }
}

void pos_wd_dev_uart1_set_reciever(bool recieve) {
    uint32_t savebits = POS_WD_DEV_UART1_AUX_MU_CNTL_REG & 0xFE;
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG = savebits | recieve;
}

void pos_wd_dev_uart1_set_transmitter(bool transmit) {
    uint32_t savebits = POS_WD_DEV_UART1_AUX_MU_CNTL_REG & 0xFD;
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG = savebits | (transmit << 1);
}

void pos_wd_dev_uart1_set_bit(bool sevenbit) {
    uint32_t savebits = POS_WD_DEV_UART1_AUX_MU_LCR_REG & 0xFE;
    POS_WD_DEV_UART1_AUX_MU_LCR_REG = savebits | sevenbit;
}