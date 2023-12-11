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

#define POS_WD_DEV_GPIO_BASE      0x3F200000
#define POS_WD_DEV_GPIO_GPFSEL0   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x00)))
#define POS_WD_DEV_GPIO_GPFSEL1   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x04)))
#define POS_WD_DEV_GPIO_GPFSEL2   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x08)))
#define POS_WD_DEV_GPIO_GPFSEL3   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x0C)))
#define POS_WD_DEV_GPIO_GPFSEL4   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x10)))
#define POS_WD_DEV_GPIO_GPFSEL5   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x14)))
#define POS_WD_DEV_GPIO_GPSET0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x1C)))
#define POS_WD_DEV_GPIO_GPSET1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x20)))
#define POS_WD_DEV_GPIO_GPCLR0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x28)))
#define POS_WD_DEV_GPIO_GPCLR1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x2C)))
#define POS_WD_DEV_GPIO_GPLEV0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x34)))
#define POS_WD_DEV_GPIO_GPLEV1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x38)))
#define POS_WD_DEV_GPIO_GPEDS0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x40)))
#define POS_WD_DEV_GPIO_GPEDS1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x44)))
#define POS_WD_DEV_GPIO_GPREN0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x4C)))
#define POS_WD_DEV_GPIO_GPREN1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x50)))
#define POS_WD_DEV_GPIO_GPFEN0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x58)))
#define POS_WD_DEV_GPIO_GPFEN1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x5C)))
#define POS_WD_DEV_GPIO_GPHEN0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x64)))
#define POS_WD_DEV_GPIO_GPHEN1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x68)))
#define POS_WD_DEV_GPIO_GPLEN0    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x70)))
#define POS_WD_DEV_GPIO_GPLEN1    (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x74)))
#define POS_WD_DEV_GPIO_GPAREN0   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x7C)))
#define POS_WD_DEV_GPIO_GPAREN1   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x80)))
#define POS_WD_DEV_GPIO_GPAFEN0   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x88)))
#define POS_WD_DEV_GPIO_GPAFEN1   (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x8C)))
#define POS_WD_DEV_GPIO_GPPUD     (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x94)))
#define POS_WD_DEV_GPIO_GPPUDCLK0 (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x98)))
#define POS_WD_DEV_GPIO_GPPUDCLK1 (*((volatile uint32_t *) (POS_WD_DEV_GPIO_BASE + 0x9C)))

/**
 * @name       GPIO Operation modes
 * 
 * Look at raspberry pi documentation for more information
 * 
 * @{
 */
#define POS_WD_DEV_GPIO_FUN_INPUT  0b000
#define POS_WD_DEV_GPIO_FUN_OUTPUT 0b001
#define POS_WD_DEV_GPIO_FUN_ALT0   0b100
#define POS_WD_DEV_GPIO_FUN_ALT1   0b101
#define POS_WD_DEV_GPIO_FUN_ALT2   0b110
#define POS_WD_DEV_GPIO_FUN_ALT3   0b111
#define POS_WD_DEV_GPIO_FUN_ALT4   0b011
#define POS_WD_DEV_GPIO_FUN_ALT5   0b010
/** @} */

bool pos_wd_dev_gpio_setpinfunction(unsigned char pin, unsigned char opmode);

/**
 * @{
 * @{
 * @{
 */