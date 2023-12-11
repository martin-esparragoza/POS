#include "wd_dev_gpio.h"
#include "wd_time.h"
#include <stdint.h>
#include <stddef.h>

bool pos_wd_dev_gpio_setpinfunction(unsigned char pin, unsigned char opmode) {
    volatile uint32_t * reg = NULL;

    if (pin <= 9) {
        reg = &POS_WD_DEV_GPIO_GPFSEL0;
    } else if (pin <= 19) {
        reg = &POS_WD_DEV_GPIO_GPFSEL1;
    } else if (pin <= 29) {
        reg = &POS_WD_DEV_GPIO_GPFSEL2;
    } else if (pin <= 39) {
        reg = &POS_WD_DEV_GPIO_GPFSEL3;
    } else if (pin <= 49) {
        reg = &POS_WD_DEV_GPIO_GPFSEL4;
    } else if (pin <= 57) {
        reg = &POS_WD_DEV_GPIO_GPFSEL5;
    } else {
        return false;
    }

    // pin % 10 as each register holds 10 pins and * 3 because each pin gets 3 bits
    unsigned short offset = (pin % 10) * 3;

    uint32_t savebits = *reg | (~(((uint32_t) 0b00000111) << offset));
    *reg = savebits | (((uint32_t) opmode) << offset);

    pos_wd_delay(150); // Somewhere in the spec it says wait 150 clock cycles. I don't know where

    return true;
}