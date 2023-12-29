#include "wd_dev_gpio.h"
#include "wd_dev_uart1.h"
#include "../include/clock.h"
#include <stdint.h>
#include <stddef.h>

void wd_dev_gpio_setpinfunction(unsigned char pin, enum wd_dev_gpio_fun fun) {
    volatile uint32_t * reg;

    if (pin <= 9) {
        reg = &WD_DEV_GPIO_GPFSEL0;
    } else if (pin <= 19) {
        reg = &WD_DEV_GPIO_GPFSEL1;
    } else if (pin <= 29) {
        reg = &WD_DEV_GPIO_GPFSEL2;
    } else if (pin <= 39) {
        reg = &WD_DEV_GPIO_GPFSEL3;
    } else if (pin <= 49) {
        reg = &WD_DEV_GPIO_GPFSEL4;
    } else { // I would write safe code, however, in the grand scheme of things a clobber is a clobber
        reg = &WD_DEV_GPIO_GPFSEL5;
    }

    // pin % 10 as each register holds 10 pins and * 3 because each pin gets 3 bits
    unsigned short offset = (pin % 10) * 3;

    uint32_t savebits = *reg & (~(0b00000111 << offset));
    *reg = savebits | (((uint32_t) fun) << offset);
}

void wd_dev_gpio_setpupd(unsigned char pin, enum wd_dev_gpio_pupd mode) {
    uint32_t reserved = WD_DEV_GPIO_GPPUD & 0xFFFFFFFC;
    WD_DEV_GPIO_GPPUD = reserved | mode;
    delay_cycles(150);

    // Store so we can reverse with easy XOR
    volatile uint32_t * reg = pin <= 31 ? &WD_DEV_GPIO_GPPUDCLK0 : &WD_DEV_GPIO_GPPUDCLK1;
    pin %= 31;
    *reg |= 1 << pin;

    delay_cycles(150);

    WD_DEV_GPIO_GPPUD = reserved;
    *reg ^= 1 << pin;
}

void wd_dev_gpio_setpupd_multi(const unsigned char pins[], unsigned pinslen, enum wd_dev_gpio_pupd mode) {
    uint32_t reserved = WD_DEV_GPIO_GPPUD & 0xFFFFFFFC;
    WD_DEV_GPIO_GPPUD = reserved | mode;
    delay_cycles(150);

    uint32_t reg1 = WD_DEV_GPIO_GPPUDCLK0;
    uint32_t reg2 = WD_DEV_GPIO_GPPUDCLK1;

    for (unsigned i = 0; i < pinslen; i++) {
        *(pins[i] <= 31 ? &reg1 : &reg2) |= 1 << (pins[i] % 31);
    }

    WD_DEV_GPIO_GPPUDCLK0 = reg1;
    WD_DEV_GPIO_GPPUDCLK1 = reg2;

    delay_cycles(150);

    WD_DEV_GPIO_GPPUD = reserved;
    WD_DEV_GPIO_GPPUDCLK0 ^= reg1;
    WD_DEV_GPIO_GPPUDCLK1 ^= reg2;
}

void wd_dev_gpio_clr(unsigned char pin) {
    volatile uint32_t * reg = pin <= 31 ? &WD_DEV_GPIO_GPCLR0 : &WD_DEV_GPIO_GPCLR1;
    *reg |= 1 << (pin % 31);
}

enum wd_dev_gpio_state wd_dev_gpio_get(unsigned char pin) {
    volatile uint32_t * reg = pin <= 31 ? &WD_DEV_GPIO_GPLEV0 : &WD_DEV_GPIO_GPLEV1;
    pin %= 31;
    // Get from register through and then shift it back to make a 0 or 1 integer
    return (*reg & (~(1 << pin))) >> pin;
}

bool wd_dev_gpio_get_event(unsigned char pin) {
    // Yes i'm lazy and copy pasted
    volatile uint32_t * reg = pin <= 31 ? &WD_DEV_GPIO_GPEDS0 : &WD_DEV_GPIO_GPEDS1;
    pin %= 31;
    // Get from register through and then shift it back to make a 0 or 1 integer
    return (*reg & (~(1 << pin))) >> pin;
}

static void write_multireg(volatile uint32_t * reg1, volatile uint32_t * reg2, unsigned char pin) {
    volatile uint32_t * reg = pin <= 31 ? reg1 : reg2;
    pin %= 31;

    *reg |= 1 << pin;
}

void wd_dev_gpio_set_event(unsigned char pin, enum wd_dev_gpio_eventopt opt) {
    if (opt & WD_DEV_GPIO_EVENTOPT_RE)
        write_multireg(&WD_DEV_GPIO_GPREN0, &WD_DEV_GPIO_GPREN1, pin);
    if (opt & WD_DEV_GPIO_EVENTOPT_FE)
        write_multireg(&WD_DEV_GPIO_GPFEN0, &WD_DEV_GPIO_GPFEN1, pin);
    if (opt & WD_DEV_GPIO_EVENTOPT_HD)
        write_multireg(&WD_DEV_GPIO_GPHEN0, &WD_DEV_GPIO_GPHEN1, pin);
    if (opt & WD_DEV_GPIO_EVENTOPT_LD)
        write_multireg(&WD_DEV_GPIO_GPLEN1, &WD_DEV_GPIO_GPLEN1, pin);
    if (opt & WD_DEV_GPIO_EVENTOPT_ARE)
        write_multireg(&WD_DEV_GPIO_GPAREN0, &WD_DEV_GPIO_GPAREN1, pin);
    if (opt & WD_DEV_GPIO_EVENTOPT_AFE)
        write_multireg(&WD_DEV_GPIO_GPAFEN0, &WD_DEV_GPIO_GPAFEN1, pin);
}

void wd_dev_gpio_set(unsigned char pin, enum wd_dev_gpio_state state) {
    volatile uint32_t * reg = pin <= 31 ? &WD_DEV_GPIO_GPSET0 : &WD_DEV_GPIO_GPSET1;
    pin %= 31;

    uint32_t savebits = *reg & (~(1 << pin));
    *reg = savebits | (state << pin);
}