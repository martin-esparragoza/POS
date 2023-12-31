/**
 * @defgroup   WD_DEV_TIMER wd dev timer
 *
 * @brief      This file implements wd dev timer.
 * 
 * @addtogroup  WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 * 
 * @defgroup   TIMER
 * @{
 */

#pragma once
#include "wd_dev.h"
#include <stdint.h>

#define WD_DEV_TIMER_BASE WD_DEV_BASE + 0x00003000
#define WD_DEV_TIMER_CS   (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x00)))
#define WD_DEV_TIMER_CLO  (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x04)))
#define WD_DEV_TIMER_CHI  (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x08)))
#define WD_DEV_TIMER_C0   (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x0C)))
#define WD_DEV_TIMER_C1   (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x10)))
#define WD_DEV_TIMER_C2   (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x14)))
#define WD_DEV_TIMER_C3   (*((volatile uint32_t *) (WD_DEV_TIMER_BASE + 0x18)))

/**
 * @brief      Reads system timer and returns current timer value
 * 
 * Value is in microseconds
 *
 * @return     Microseconds
 */
uint64_t wd_dev_timer_currenttimeus();

/**
 * @brief      Uses system clock to wait for a number of microseconds
 *
 * @param[in]  us    Num microseconds
 */
void wd_dev_timer_waitus(uint64_t us);

/**
 * @brief      Uses system clock to wait for a number of miliseconds
 *
 * @param[in]  ms    Num miliseconds
 */
void wd_dev_timer_waitms(uint64_t ms);

/**
 * @}
 * @}
 * @}
 */
