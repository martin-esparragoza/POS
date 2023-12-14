#include "wd_dev_gpio.h"
#include "wd_time.h"
#include <stdint.h>
#include <stddef.h>

void pos_wd_dev_gpio_setpinfunction(unsigned char pin, enum pos_wd_dev_gpio_fun fun) {
    volatile uint32_t * reg;

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
    } else { // I would write safe code, however, in the grand scheme of things a clobber is a clobber
        reg = &POS_WD_DEV_GPIO_GPFSEL5;
    }

    // pin % 10 as each register holds 10 pins and * 3 because each pin gets 3 bits
    unsigned short offset = (pin % 10) * 3;

    uint32_t savebits = *reg & (~(((uint32_t) 0b00000111) << offset));
    *reg = savebits | (((uint32_t) fun) << offset);
}

void pos_wd_dev_gpio_setpupd(unsigned char pin, enum pos_wd_dev_gpio_pupd mode) {
    uint32_t reserved = POS_WD_DEV_GPIO_GPPUD & 0xFFFFFFFC;
    POS_WD_DEV_GPIO_GPPUD = reserved | mode;
    pos_wd_delay(150);

    // We actually want to store it this time
    volatile uint32_t * reg = pin >= 31 ? &POS_WD_DEV_GPIO_GPPUDCLK0 : &POS_WD_DEV_GPIO_GPPUDCLK1;
    pin %= 31;
    *reg |= 1 << pin;

    pos_wd_delay(150);

    POS_WD_DEV_GPIO_GPPUD = reserved;
    *reg ^= 1 << pin;
}

void pos_wd_dev_gpio_clr(unsigned char pin) {
    volatile uint32_t * reg = pin <= 31 ? &POS_WD_DEV_GPIO_GPCLR0 : &POS_WD_DEV_GPIO_GPCLR1;
    *reg |= 1 << (pin % 31);
}

enum pos_wd_dev_gpio_state pos_wd_dev_gpio_get(unsigned char pin) {
    volatile uint32_t * reg = pin <= 31 ? &POS_WD_DEV_GPIO_GPLEV0 : &POS_WD_DEV_GPIO_GPLEV1;
    pin %= 31;
    // Get from register through and then shift it back to make a 0 or 1 integer
    return (*reg & (~(1 << pin))) >> pin;
}

bool pos_wd_dev_gpio_get_event(unsigned char pin) {
    // Yes i'm lazy and copy pasted
    volatile uint32_t * reg = pin <= 31 ? &POS_WD_DEV_GPIO_GPEDS0 : &POS_WD_DEV_GPIO_GPEDS1;
    pin %= 31;
    // Get from register through and then shift it back to make a 0 or 1 integer
    return (*reg & (~(1 << pin))) >> pin;
}

static void write_multireg(volatile uint32_t * reg1, volatile uint32_t * reg2, unsigned char pin) {
    volatile uint32_t * reg = pin <= 31 ? reg1 : reg2;
    pin %= 31;

    *reg |= 1 << pin;
}

void pos_wd_dev_gpio_set_event(unsigned char pin, enum pos_wd_dev_gpio_eventopt opt) {
    if (opt & POS_WD_DEV_GPIO_EVENTOPT_RE)
        write_multireg(&POS_WD_DEV_GPIO_GPREN0, &POS_WD_DEV_GPIO_GPREN1, pin);
    if (opt & POS_WD_DEV_GPIO_EVENTOPT_FE)
        write_multireg(&POS_WD_DEV_GPIO_GPFEN0, &POS_WD_DEV_GPIO_GPFEN1, pin);
    if (opt & POS_WD_DEV_GPIO_EVENTOPT_HD)
        write_multireg(&POS_WD_DEV_GPIO_GPHEN0, &POS_WD_DEV_GPIO_GPHEN1, pin);
    if (opt & POS_WD_DEV_GPIO_EVENTOPT_LD)
        write_multireg(&POS_WD_DEV_GPIO_GPLEN1, &POS_WD_DEV_GPIO_GPLEN1, pin);
    if (opt & POS_WD_DEV_GPIO_EVENTOPT_ARE)
        write_multireg(&POS_WD_DEV_GPIO_GPAREN0, &POS_WD_DEV_GPIO_GPAREN1, pin);
    if (opt & POS_WD_DEV_GPIO_EVENTOPT_AFE)
        write_multireg(&POS_WD_DEV_GPIO_GPAFEN0, &POS_WD_DEV_GPIO_GPAFEN1, pin);
}