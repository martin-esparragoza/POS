#include "wd_dev_uart1.h"
#include "wd_dev_gen.h"
#include "wd_time.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void pos_wd_dev_uart1_enable() {
    POS_WD_DEV_GEN_AUX_ENABLES |= 1;
    pos_wd_delay(2);
}

void pos_wd_dev_uart1_disable() {
    POS_WD_DEV_GEN_AUX_ENABLES &= ~1;
    pos_wd_delay(2);
}

bool pos_wd_dev_uart1_set_baud(unsigned baud) {
    unsigned reg = (250000 / (8 * baud)) - 1;
    if (reg > ((uint16_t) ~0)) {
        return false;
    }
    POS_WD_DEV_UART1_AUX_MU_BAUD_REG = (uint16_t) reg;
    pos_wd_delay(2);
    return true;
}

// TODO: Timeout
void pos_wd_dev_uart1_write_sync(uint8_t * data, size_t length) {
    unsigned i = 0;
    while (i < length) {
        if ((POS_WD_DEV_UART1_AUX_MU_LSR_REG & 0b00100000) > 0) { // Transmit FIFO has at least one byte ready
            POS_WD_DEV_UART1_AUX_MU_IO_REG |= data[i++];
        }
        pos_wd_delay(2);
    }
}

bool pos_wd_dev_uart1_init(unsigned baud) {
    pos_wd_dev_uart1_disable();
    // Enable GPIO TODO

    // https://github.com/s-matyukevich/raspberry-pi-os/blob/master/src/lesson01/src/mini_uart.c
    // TODO: GPIO

    pos_wd_dev_uart1_enable();
    if (!pos_wd_dev_uart1_set_baud(baud))
        return false;
    return true;
}