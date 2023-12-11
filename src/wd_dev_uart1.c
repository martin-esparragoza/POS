#include "wd_dev_uart1.h"
#include "wd_dev_gen.h"
#include "wd_time.h"
#include "wd_dev_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void pos_wd_dev_uart1_enable() {
    POS_WD_DEV_GEN_AUX_ENABLES |= 1;
}

void pos_wd_dev_uart1_disable() {
    POS_WD_DEV_GEN_AUX_ENABLES &= ~1;
}

bool pos_wd_dev_uart1_set_baud(unsigned baud) {
    unsigned reg = (250000 / (8 * baud)) - 1;
    if (reg > ((uint16_t) ~0)) {
        return false;
    }
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

bool pos_wd_dev_uart1_init(unsigned baud) {
    //pos_wd_dev_uart1_disable();
    POS_WD_DEV_GEN_AUX_ENABLES |= 1;

    //pos_wd_dev_gpio_setpinfunction(14, POS_WD_DEV_GPIO_FUN_ALT5);
    //pos_wd_dev_gpio_setpinfunction(15, POS_WD_DEV_GPIO_FUN_ALT5);

    /*uint32_t selector = POS_WD_DEV_GPIO_GPFSEL1;
    selector &= ~(7<<12);
    selector |= 2<<12;
    selector &= ~(7<<15);
    selector |= 2<<15;
    POS_WD_DEV_GPIO_GPFSEL1 = selector;


    POS_WD_DEV_GPIO_GPPUD = 0;
    pos_wd_delay(150);

    POS_WD_DEV_GPIO_GPPUDCLK0 = (1<<14)|(1<<15);
    pos_wd_delay(150);*/

    POS_WD_DEV_UART1_AUX_MU_CNTL_REG &= 0xFFFFFFFE;
    POS_WD_DEV_UART1_AUX_MU_IER_REG &= 0xFFFFFFFE;
    POS_WD_DEV_UART1_AUX_MU_LCR_REG |= 3;
    POS_WD_DEV_UART1_AUX_MU_MCR_REG &= 0xFFFFFFFD;
    POS_WD_DEV_UART1_AUX_MU_BAUD_REG = 0x10E;
    POS_WD_DEV_UART1_AUX_MU_IIR_REG |= 0x6;
    POS_WD_DEV_UART1_AUX_MU_CNTL_REG |= 0x3;

    POS_WD_DEV_UART1_AUX_MU_IO_REG = 'A';


    //if (!pos_wd_dev_uart1_set_baud(baud))
    //    return false;
    //POS_WD_DEV_UART1_AUX_MU_BAUD_REG = 270;

    //POS_WD_DEV_UART1_AUX_MU_CNTL_REG = 3;

    return true;
}