/**
 * @file

 * @brief      WD only barebones uart1 drivers
 * 
 * All operations are synchronous <br>
 * RX and CTX operations take 2 cycles to process (software added more delay sometimes for saftey)
 * 
 * @see        <a href = "https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf">Reference used</a>
 * 
 * @addtogroup WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 *
 * @defgroup   UART1
 * UART1
 * @{
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define POS_WD_DEV_UART1_AUX_MU_IO_REG   (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x40)))
#define POS_WD_DEV_UART1_AUX_MU_IER_REG  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x44)))
#define POS_WD_DEV_UART1_AUX_MU_IIR_REG  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x48)))
#define POS_WD_DEV_UART1_AUX_MU_LCR_REG  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x4C)))
#define POS_WD_DEV_UART1_AUX_MU_MCR_REG  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x50)))
#define POS_WD_DEV_UART1_AUX_MU_LSR_REG  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x54)))
#define POS_WD_DEV_UART1_AUX_MU_MSR_REG  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x58)))
#define POS_WD_DEV_UART1_AUX_MU_SCRATCH  (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x5C)))
#define POS_WD_DEV_UART1_AUX_MU_CNTL_REG (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x60)))
#define POS_WD_DEV_UART1_AUX_MU_STAT_REG (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x64)))
#define POS_WD_DEV_UART1_AUX_MU_BAUD_REG (*((volatile uint32_t *) (POS_WD_DEV_GEN_AUX_BASE + 0x68)))

/**
 * @brief      Enables UART1 through AUX_ENABLES reg
 */
void pos_wd_dev_uart1_enable();

/**
 * @brief      Disables UART1 through AUX_ENABLES reg
 */
void pos_wd_dev_uart1_disable();

/**
 * @brief      Sets the baud rate of the UARt1
 * 
 * Assumes the system clock is at 250MHz <br>
 * Therefore the minimum and maximum baud rates are 476 baud and 31.25 mega baud respectively
 *
 * @param[in]  baud  The baud rate
 *
 * @return     False if calculated buad value is unable to be fit into 16 bits (too big)
 */
bool pos_wd_dev_uart1_set_baud(unsigned baud);

/**
 * @brief      Blocking write of data to UART1
 *
 * @param[in]  data    The data
 * @param[in]  length  The length of the data
 */
void pos_wd_dev_uart1_write_sync(uint8_t * data, size_t length);

/**
 * @brief      Initializes the UART1
 *
 * @param[in]  baud  The baud rate that is supplied to `pos_wd_dev_uart1_set_baud`
 *
 * @return     False if `pos_wd_dev_uart1_set_baud` returns false or gpio error
 */
bool pos_wd_dev_uart1_init(unsigned baud);

/**
 * @}
 * @}
 * @}
 */