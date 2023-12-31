/**
 * @file
 * 
 * @brief      Debug utils
 *
 * @addtogroup WD
 * @{
 * 
 * @addtogroup STDIO
 * @{
 */

#pragma once

#include "wd_dev_uart1.h"
#include "../include/config.h"
#include <stdint.h>

extern void wd_panic;

// Hack
#ifdef UART1_DEBUG
#define __UART1_DEBUG_PRINTF(format, ...) wd_dev_uart1_printf(format, ##__VA_ARGS__) /**< DO NOT USE */
#else
#define __UART1_DEBUG_PRINTF(format, ...)
#endif

#define WD_INFO(format, ...)       __UART1_DEBUG_PRINTF("[WD\tINFO\t%s:%d] " format, __FILE__, (uintmax_t) __LINE__, ##__VA_ARGS__)
#define WD_WARN(format, ...)       __UART1_DEBUG_PRINTF("[WD\tWARN\t%s:%d] " format, __FILE__, (uintmax_t) __LINE__, ##__VA_ARGS__)
#define WD_ERROR_SOFT(format, ...) __UART1_DEBUG_PRINTF("[WD\tERROR\t%s:%d] " format, __FILE__, (uintmax_t) __LINE__, ##__VA_ARGS__);
#define WD_ERROR(format, ...)      WD_ERROR_SOFT(format, ##__VA_ARGS__); goto wd_panic

#define WD_ASSERT_SOFT(condition, then) \
    if (!(condition)) { \
        WD_ERROR_SOFT("Soft assertion %s failed\n", __FILE__, __LINE__, #condition); \
        then; \
    }


#define WD_ASSERT_HARD(condition, then) \
    if (!(condition)) { \
        WD_ERROR_SOFT("Hard assertion %s failed\n", __FILE__, __LINE__, #condition); \
        then; \
        goto wd_panic; \
    }

