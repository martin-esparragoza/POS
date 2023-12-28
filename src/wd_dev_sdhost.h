/**
 * @file
 *
 * @addtogroup WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 * 
 * @addtogroup SD
 * @{
 *
 * @defgroup   SDHOST
 * Registers + Other things for driver imeplementation <br>
 * Functions are defined in wd_dev_sd.h
 * @{
 * 
 * @brief      SD host controller for raspberry pi 3
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

#define WD_DEV_SDHOST_BASE   0x7E202000
#define WD_DEV_SDHOST_SDCMD  (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x00)))
#define WD_DEV_SDHOST_SDARG  (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x04)))
#define WD_DEV_SDHOST_SDTOUT (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x08)))
#define WD_DEV_SDHOST_SDCDIV (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x0c)))
#define WD_DEV_SDHOST_SDRSP0 (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x10)))
#define WD_DEV_SDHOST_SDRSP1 (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x14)))
#define WD_DEV_SDHOST_SDRSP2 (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x18)))
#define WD_DEV_SDHOST_SDRSP3 (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x1c)))
#define WD_DEV_SDHOST_SDHSTS (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x20)))
#define WD_DEV_SDHOST_SDVDD  (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x30)))
#define WD_DEV_SDHOST_SDEDM  (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x34)))
#define WD_DEV_SDHOST_SDHCFG (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x38)))
#define WD_DEV_SDHOST_SDHBCT (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x3c)))
#define WD_DEV_SDHOST_SDDATA (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x40)))
#define WD_DEV_SDHOST_SDHBLC (*((volatile uint32_t *) (wd_SDHOST_BASE + 0x50)))

/**
 * @}
 * @}
 * @}
 */
