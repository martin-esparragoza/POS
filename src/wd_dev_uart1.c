#include "wd_dev_uart1.h"
#include "wd_dev_gen.h"
#include "wd_dev_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void pos_wd_dev_uart1_init() {
    pos_wd_dev_gpio_setpupd(14, POS_WD_DEV_GPIO_PUPD_DOWN);
    pos_wd_dev_gpio_setpupd(15, POS_WD_DEV_GPIO_PUPD_DOWN);
    pos_wd_dev_gpio_setpinfunction(14, POS_WD_DEV_GPIO_FUN_ALT5); // Transfer line
    pos_wd_dev_gpio_setpinfunction(15, POS_WD_DEV_GPIO_FUN_ALT5); // Recieve line
    pos_wd_dev_gpio_clr(14);
    pos_wd_dev_gpio_clr(15);
    
    // Initialize the UART1 (mini uart)
    pos_wd_dev_uart1_enable();
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG = 0; // Disable stuff like auto folow control
    POS_WD_DEV_UART1_AUX_MU_IER_REG = 0; // Disable interrupts
    POS_WD_DEV_UART1_AUX_MU_MCR_REG = 0; // RTS high (unknown if needed)
    pos_wd_dev_uart1_enable_sevenbit();
    pos_wd_dev_uart1_set_baud(115200); // This should NEVER error
    pos_wd_dev_uart1_enable_transmitter();
}

// Garbage function to shove in a mask
static void set_bit(volatile uint32_t * reg, uint32_t bit) {
    uint32_t savebits = *reg & (~bit);
    *reg = savebits | bit;
}

void pos_wd_dev_uart1_set_enabled(bool enabled) {
    set_bit(&POS_WD_DEV_GEN_AUX_ENABLES, enabled);
}

bool pos_wd_dev_uart1_set_baud(unsigned baud) {
    unsigned reg = (250000000 / (8 * baud)) - 1;
    if (reg > ((uint16_t) ~0))
        return false;

    uint32_t reserved = POS_WD_DEV_UART1_AUX_MU_BAUD_REG & 0xFFFF0000;
    POS_WD_DEV_UART1_AUX_MU_BAUD_REG = reserved | baud;
    return true;
}

void pos_wd_dev_uart1_write_char(char data) {
    while ((POS_WD_DEV_UART1_AUX_MU_LSR_REG & 0b00100000) <= 0) {;}
    uint32_t reserved = POS_WD_DEV_UART1_AUX_MU_IO_REG & 0xFFFFFF00;
    POS_WD_DEV_UART1_AUX_MU_IO_REG = reserved | data;
}

void pos_wd_dev_uart1_write_data(uint8_t * data, size_t length) {
    unsigned i = 0;
    while (i < length) {
        pos_wd_dev_uart1_write_char(data[i++]);
    }
}

void pos_wd_dev_uart1_set_reciever(bool recieve) {
    set_bit(&POS_WD_DEV_UART1_AUX_MU_CNTL_REG, recieve);
}

void pos_wd_dev_uart1_set_transmitter(bool transmit) {
    set_bit(&POS_WD_DEV_UART1_AUX_MU_CNTL_REG, transmit << 1);
}

void pos_wd_dev_uart1_set_bit(bool sevenbit) {
    set_bit(&POS_WD_DEV_UART1_AUX_MU_LCR_REG, sevenbit);
}