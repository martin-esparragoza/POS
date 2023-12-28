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

#if PIV == PI2 || PI3AP
#define WD_DEV_GEN_AUX_BASE     0x3F215000
#else
#warning DEFINING WD_DEV_GEN_AUX_BASE as 0x3F215000 BY DEFAULT! UNTESTED CODE IS BEING COMPILED!
#endif
#define WD_DEV_GEN_AUX_IRQ      (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x00)))
#define WD_DEV_GEN_AUX_ENABLES  (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x04)))

/**
 * @}
 * @}
 */