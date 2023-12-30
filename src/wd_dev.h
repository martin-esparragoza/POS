/**
 * @file
 *
 * @brief      Generic IO devices mapping
 * 
 * Dear reader of this file. It's pretty scuffed. Sorry. <br>
 * Other than that, this file is a hybrid between AUX defines and general defines
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

#if PIV == PI2 || PIV == PI3B
#define WD_DEV_BASE 0x3F000000
#endif

#if PIV == PI2 || PIV == PI3AP
#define WD_DEV_GEN_AUX_BASE     WD_DEV_BASE + 0x00215000
#endif
#define WD_DEV_GEN_AUX_IRQ      (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x00)))
#define WD_DEV_GEN_AUX_ENABLES  (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x04)))

/**
 * @}
 * @}
 */