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
 * UART1 <br>
 * <b>NOTE: UART1 must be enabled before changing anything about it (e.g. 7 or 8 bit transmission)</b>
 * @{
 */

#pragma once
#include "wd_dev_gen.h"
#include "wd_stdio.h"
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
 * @brief      Turns on/off the UART1
 * 
 * <b>UART1 MUST BE ANBLED BEFORE ANY OTHER FUNCTIONS ARE USED</b> <br>
 * Also no checks are made if it is enabled
 * 
 * @param[in]  enabled  True to turn on false to turn off
 */
void pos_wd_dev_uart1_set_enabled(bool enabled);
#define pos_wd_dev_uart1_enable() pos_wd_dev_uart1_set_enabled(true)
#define pos_wd_dev_uart1_disable() pos_wd_dev_uart1_set_enabled(false)

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
 * @brief      Write a single character to the FIFO
 *
 * @param[in]  data  Character
 */
void pos_wd_dev_uart1_write_char(char data);

/**
 * @brief      Blocking write of data to UART1
 *
 * @param[in]  data    The data
 * @param[in]  length  The length of the data
 */
void pos_wd_dev_uart1_write_data(uint8_t * data, size_t length);

/**
 * @brief      Initializes the UART1
 *
 * @param[in]  baud  The baud rate that is supplied to `pos_wd_dev_uart1_set_baud`
 *
 * @return     False if `pos_wd_dev_uart1_set_baud` returns false or gpio error
 */
bool pos_wd_dev_uart1_init(unsigned baud);

/**
 * @brief      Turns on/off recieve functionality
 * 
 * @param[in]  recieve True to turn on and false to turn off
 */
void pos_wd_dev_uart1_set_reciever(bool recieve);
#define pos_wd_dev_uart1_enable_reciever() pos_wd_dev_uart1_set_reciever(true)
#define pos_wd_dev_uart1_disable_reciever() pos_wd_dev_uart1_set_reciever(false)

/**
 * @brief      Turn on/off transmit functionality
 * 
 * @param[in]  transmit True to enable false to disable
 */
void pos_wd_dev_uart1_set_transmitter(bool transmit);
#define pos_wd_dev_uart1_enable_transmitter() pos_wd_dev_uart1_set_transmitter(true)
#define pos_wd_dev_uart1_disable_transmitter() pos_wd_dev_uart1_set_transmitter(false)

/**
 * @brief      Activates 7 or 8 bit transmission
 * 
 * @param[in]  sevenbit True for 7 bit transmission and false for 8
 */
void pos_wd_dev_uart1_set_bit(bool sevenbit);
#define pos_wd_dev_uart1_enable_sevenbit() pos_wd_dev_uart1_set_bit(true)
#define pos_wd_dev_uart1_enable_eightbit() pos_wd_dev_uart1_set_bit(false)

/**
 * @brief      Sets RTS pin to high or low
 * 
 * <b>Remember to enable GPIO functionality</b>
 *
 * @param[in]  high  True for set high and false for otherwise
 */
void pos_wd_dev_uart1_set_rts(bool high);
#define pos_wd_dev_uart1_enable_rts() pos_wd_dev_uart1_set_rts(true)
#define pos_wd_dev_uart1_disable_rts() pos_wd_dev_uart1_set_rts(false)

/**
 * @addtogroup STDIO
 * @{
 */
#define pos_wd_dev_uart1_printf(format, ...) pos_wd_fprintf(&pos_wd_dev_uart1_write_char, format, __VA_ARGS__)
/** @} */

/**
 * @}
 * @}
 * @}
 */