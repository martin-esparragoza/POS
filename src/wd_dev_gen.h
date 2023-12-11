/**
 * @file
 *
 * @brief      I/O device address mapping
 *
 * @see        <a href = "https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf">Reference used</a>
 * 
 * @addtogroup WD
 * @{
 * 
 * @defgroup   DEV
 * Devices
 * @{
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

#define POS_WD_DEV_GEN_AUX_BASE     0x3F215000
#define POS_WD_DEV_GEN_AUX_IRQ      (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x00)))
#define POS_WD_DEV_GEN_AUX_ENABLES  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x04)))

/**
 * @}
 * @}
 */