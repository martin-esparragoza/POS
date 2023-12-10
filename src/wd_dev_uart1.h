/**
 * @file
 *
 * @brief WD only barebones uart1 drivers
 * 
 * All operations are synchronous <br>
 * RX and CTX operations take 2 cycles to process (software added more delay sometimes for saftey)
 * 
 * @see <a href = "https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf">Reference used</a>
 * 
 * \addtogroup WD
 * @{
 * 
 * \addtogroup DEV
 * @{
 *
 * @defgroup UART1
 * UART1
 * @{
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define POS_WD_DEV_UART1_AUX_MU_IO_REG   (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x40))
#define POS_WD_DEV_UART1_AUX_MU_IER_REG  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x44))
#define POS_WD_DEV_UART1_AUX_MU_IIR_REG  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x48))
#define POS_WD_DEV_UART1_AUX_MU_LCR_REG  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x4C))
#define POS_WD_DEV_UART1_AUX_MU_MCR_REG  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x50))
#define POS_WD_DEV_UART1_AUX_MU_LSR_REG  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x54))
#define POS_WD_DEV_UART1_AUX_MU_MSR_REG  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x58))
#define POS_WD_DEV_UART1_AUX_MU_SCRATCH  (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x5C))
#define POS_WD_DEV_UART1_AUX_MU_CNTL_REG (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x60))
#define POS_WD_DEV_UART1_AUX_MU_STAT_REG (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x64))
#define POS_WD_DEV_UART1_AUX_MU_BAUD_REG (*((volatile uint32_t *) POS_WD_DEV_GEN_AUX_BASE + 0x68))

void pos_wd_dev_uart1_enable();
void pos_wd_dev_uart1_disable();

/**
 * @brief Set baud rate of UART1
 *
 * Assumes system clock is 250MHz
 *
 * @return False if could not set baudrate within 16 bits
 */
bool pos_wd_dev_uart1_set_baud(unsigned baud);
void pos_wd_dev_uart1_write_sync(uint8_t * data, size_t length);

/**
 * @brief Initalize the internal UART1 auxillary
 * 
 * Enables needed GPIO pins, Enables the UART1 auxillary in iod, sets the baud rate, etc. <br>
 * 
 * @return Failed initalization if false
 */
bool pos_wd_dev_uart1_init(unsigned baud);

/**
 * @}
 * @}
 * @}
 */