/**
 * @file
 * 
 * @brief      WD only GPIO drivers
 * 
 * <b>TODO: This is only for RPI2. Write it for nessicary versions. </b>
 * 
 * @addtogroup WD
 * @{
 *
 * @addtogroup DEV
 * @{
 *
 * @defgroup   GPIO
 * GPIO
 * @{
 */

#pragma once
#include "wd_dev_gen.h"
#include <stdint.h>

#define WD_DEV_GPIO_BASE      0x3F200000
#define WD_DEV_GPIO_GPFSEL0   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x00)))
#define WD_DEV_GPIO_GPFSEL1   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x04)))
#define WD_DEV_GPIO_GPFSEL2   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x08)))
#define WD_DEV_GPIO_GPFSEL3   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x0C)))
#define WD_DEV_GPIO_GPFSEL4   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x10)))
#define WD_DEV_GPIO_GPFSEL5   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x14)))
#define WD_DEV_GPIO_GPSET0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x1C)))
#define WD_DEV_GPIO_GPSET1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x20)))
#define WD_DEV_GPIO_GPCLR0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x28)))
#define WD_DEV_GPIO_GPCLR1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x2C)))
#define WD_DEV_GPIO_GPLEV0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x34)))
#define WD_DEV_GPIO_GPLEV1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x38)))
#define WD_DEV_GPIO_GPEDS0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x40)))
#define WD_DEV_GPIO_GPEDS1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x44)))
#define WD_DEV_GPIO_GPREN0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x4C)))
#define WD_DEV_GPIO_GPREN1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x50)))
#define WD_DEV_GPIO_GPFEN0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x58)))
#define WD_DEV_GPIO_GPFEN1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x5C)))
#define WD_DEV_GPIO_GPHEN0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x64)))
#define WD_DEV_GPIO_GPHEN1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x68)))
#define WD_DEV_GPIO_GPLEN0    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x70)))
#define WD_DEV_GPIO_GPLEN1    (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x74)))
#define WD_DEV_GPIO_GPAREN0   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x7C)))
#define WD_DEV_GPIO_GPAREN1   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x80)))
#define WD_DEV_GPIO_GPAFEN0   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x88)))
#define WD_DEV_GPIO_GPAFEN1   (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x8C)))
#define WD_DEV_GPIO_GPPUD     (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x94)))
#define WD_DEV_GPIO_GPPUDCLK0 (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x98)))
#define WD_DEV_GPIO_GPPUDCLK1 (*((volatile uint32_t *) (WD_DEV_GPIO_BASE + 0x9C)))

enum wd_dev_gpio_state {
    WD_DEV_GPIO_STATE_HIGH = 1,
    WD_DEV_GPIO_STATE_LOW =  0
};

/**
 * @brief      Functions for setpinfunction
 * 
 * Check the raspberry pi documentation! Some ALTS are not allowed!
 */
enum wd_dev_gpio_fun {
    WD_DEV_GPIO_FUN_INPUT =  0b000, /// All pins can use this (besides internal)
    WD_DEV_GPIO_FUN_OUTPUT = 0b001, /// All pins can use this (besides internal)
    WD_DEV_GPIO_FUN_ALT0 =   0b100,
    WD_DEV_GPIO_FUN_ALT1 =   0b101,
    WD_DEV_GPIO_FUN_ALT2 =   0b110,
    WD_DEV_GPIO_FUN_ALT3 =   0b111,
    WD_DEV_GPIO_FUN_ALT4 =   0b011,
    WD_DEV_GPIO_FUN_ALT5 =   0b010
};

/**
 * @brief      Set a specific pin to use an alternate function
 *
 * @param[in]  pin     Pin should be between 0-57
 * @param[in]  opmode  See enum
 */
void wd_dev_gpio_setpinfunction(unsigned char pin, enum wd_dev_gpio_fun fun);

/**
 * @brief      Pull up / pull down
 * 
 * Allows you to set a gpio pin to pull up or pull down or float
 */
enum wd_dev_gpio_pupd {
    WD_DEV_GPIO_PUPD_FLOAT = 0b00,
    WD_DEV_GPIO_PUPD_UP =    0b10,
    WD_DEV_GPIO_PUPD_DOWN =  0b01
};

/**
 * @brief      Sets a specific pin to pull up, pull down, or float
 * 
 * This could definitley be better and just be 1 write. However, its the WD and I don't care
 *
 * @param[in]  pin   Pin should be 0-57. Checks are not done
 * @param[in]  mode  See enum
 */
void wd_dev_gpio_setpupd(unsigned char pin, enum wd_dev_gpio_pupd mode);

/**
 * @brief      Clears a pin
 *
 * @param[in]  pin   0-57 no checks
 */
void wd_dev_gpio_clr(unsigned char pin);

/**
 * @brief      Gets value of pin
 * 
 * Works if pin is set to input
 *
 * @param[in]  pin   0-57 no checks
 *
 * @return     enum high/low
 */
enum wd_dev_gpio_state wd_dev_gpio_get(unsigned char pin);

/**
 * @brief      Returns event bit
 * 
 * Tells you if event was detected on GPIO pin
 *
 * @param[in]  pin   0-57 no checks
 *
 * @return     True if event detected
 */
bool wd_dev_gpio_get_event(unsigned char pin);

/// Used only for set_event function
enum wd_dev_gpio_eventopt {
    WD_DEV_GPIO_EVENTOPT_RE =  1,      /// Rising edge detect
    WD_DEV_GPIO_EVENTOPT_FE =  1 << 1, /// Falling edge detect
    WD_DEV_GPIO_EVENTOPT_HD =  1 << 2, /// High detect
    WD_DEV_GPIO_EVENTOPT_LD =  1 << 3, /// Low detect
    WD_DEV_GPIO_EVENTOPT_ARE = 1 << 4, /// Async rising edge
    WD_DEV_GPIO_EVENTOPT_AFE = 1 << 5, /// Async falling edge
};

/**
 * @brief      Set event detector to use these
 *
 * @param[in]  pin     0-57 no checks
 * @param[in]  opt     This is a bitmap
 */
void wd_dev_gpio_set_event(unsigned char pin, enum wd_dev_gpio_eventopt opt);

/**
 * @brief      Set to high or low
 * 
 * Ignored if pin is not set as an output
 *
 * @param[in]  state  High or low state
 */
void wd_dev_gpio_set(unsigned char pin, enum wd_dev_gpio_state state);

/**
 * @}
 * @}
 * @}
 */