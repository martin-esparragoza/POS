#include "wd_dev_uart1.h"
#include "wd_dev_gen.h"
#include "wd_time.h"
#include "wd_dev_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void pos_wd_dev_uart1_set_enabled(bool enabled) {
    POS_WD_DEV_GEN_AUX_ENABLES &= (~((uint32_t) 1)) | enabled;
}

bool pos_wd_dev_uart1_set_baud(unsigned baud) {
    unsigned reg = (250000000 / (8 * baud)) - 1;
    if (reg > ((uint16_t) ~0))
        return false;

    uint32_t reserved = POS_WD_DEV_UART1_AUX_MU_BAUD_REG & 0xFFFF0000;
    POS_WD_DEV_UART1_AUX_MU_BAUD_REG = reserved | baud;
    return true;
}

// TODO: Timeout
void pos_wd_dev_uart1_write_sync(uint8_t * data, size_t length) {
    unsigned i = 0;
    while (i < length) {
        if ((POS_WD_DEV_UART1_AUX_MU_LSR_REG & 0b00100000) > 0) { // Transmit FIFO has at least one byte ready
            uint32_t reserved = POS_WD_DEV_UART1_AUX_MU_IO_REG & 0xFFFFFF00;
            POS_WD_DEV_UART1_AUX_MU_IO_REG = reserved | data[i++];
        }
    }
}

void pos_wd_dev_uart1_set_reciever(bool recieve) {
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG &= (~((uint32_t) 1)) | recieve;
}

void pos_wd_dev_uart1_set_transmitter(bool transmit) {
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG &= (~((uint32_t) 1 << 1)) | transmit;
}

void pos_wd_dev_uart1_set_bit(bool sevenbit) {
    POS_WD_DEV_UART1_AUX_MU_LCR_REG &= (~((uint32_t) 1)) | sevenbit << 1;
}

void pos_wd_dev_uart1_set_rts(bool high) {
    POS_WD_DEV_UART1_AUX_MU_MCR_REG &= (~((uint32_t) 1 << 1)) | high << 1;
}