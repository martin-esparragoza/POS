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
#include "wd_dev.h"
#include "wd_stdio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define WD_DEV_UART1_IO               (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x40)))
#define WD_DEV_UART1_IO_LS8BAUD       0xFF
#define WD_DEV_UART1_IO_LS8BAUD_S     0
#define WD_DEV_UART1_IO_TRANS         0xFF
#define WD_DEV_UART1_IO_TRANS_S       0
#define WD_DEV_UART1_IO_RCV           0xFF
#define WD_DEV_UART1_IO_RCV_S         0
#define WD_DEV_UART1_IO_MSK           0xFF

#define WD_DEV_UART1_IIR              (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x44)))
#define WD_DEV_UART1_IIR_MS8BAUD      0xFF
#define WD_DEV_UART1_IIR_MS8BAUD_S    0
#define WD_DEV_UART1_IIR_ERI          0x02
#define WD_DEV_UART1_IIR_ERI_S        1
#define WD_DEV_UART1_IIR_ETI          0x01
#define WD_DEV_UART1_IIR_ETI_S        0
#define WD_DEV_UART1_IIR_MSK          0xFF

#define WD_DEV_UART1_IER              (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x48)))
#define WD_DEV_UART1_IER_FIFOEN       0xC0
#define WD_DEV_UART1_IER_FIFOEN_S     6
#define WD_DEV_UART1_IER_IIDCLR       0x06
#define WD_DEV_UART1_IER_IIDCLR_S     1
#define WD_DEV_UART1_IER_IP           0x01
#define WD_DEV_UART1_IER_IP_S         0
#define WD_DEV_UART1_IER_MSK          0xC7

#define WD_DEV_UART1_LCR              (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x4C)))
#define WD_DEV_UART1_LCR_DLABA        0x80
#define WD_DEV_UART1_LCR_DLABA_S      7
#define WD_DEV_UART1_LCR_BRK          0x04
#define WD_DEV_UART1_LCR_BRK_S        2
#define WD_DEV_UART1_LCR_DATSZ        0x01
#define WD_DEV_UART1_LCR_DATSZ_S      0
#define WD_DEV_UART1_LCR_MSK          0x85

#define WD_DEV_UART1_MCR              (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x50)))
#define WD_DEV_UART1_MCR_RTS          0x02
#define WD_DEV_UART1_MCR_RTS_S        1
#define WD_DEV_UART1_MCR_MSK          0x02

#define WD_DEV_UART1_LSR              (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x54)))
#define WD_DEV_UART1_LSR_TRANSIDLE    0x40
#define WD_DEV_UART1_LSR_TRANSIDLE_S  6
#define WD_DEV_UART1_LSR_TRANSEP      0x20
#define WD_DEV_UART1_LSR_TRANSEP_S    5
#define WD_DEV_UART1_LSR_RCVOVER      0x02
#define WD_DEV_UART1_LSR_RCVOVER_S    1
#define WD_DEV_UART1_LSR_DATAREADY    0x01
#define WD_DEV_UART1_LSR_DATAREADY_S  0
#define WD_DEV_UART1_LSR_MSK          0x63

#define WD_DEV_UART1_MSR              (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x58)))
#define WD_DEV_UART1_MSR_CTSINV       0x10
#define WD_DEV_UART1_MSR_CTSINV_s     4
#define WD_DEV_UART1_MSR_MSK          0x10

#define WD_DEV_UART1_SCRATCH          (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x5C)))
#define WD_DEV_UART1_SCRATCH_MSK      0xFF

#define WD_DEV_UART1_CNTL             (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x60)))
#define WD_DEV_UART1_CNTL_CTSASS      0x80
#define WD_DEV_UART1_CNTL_CTSASS_S    7
#define WD_DEV_UART1_CNTL_RTSASS      0x40
#define WD_DEV_UART1_CNTL_RTSASS_S    6
#define WD_DEV_UART1_CNTL_RTSAUTO     0x30
#define WD_DEV_UART1_CNTL_RTSAUTO_S   4
#define WD_DEV_UART1_CNTL_CTSAUTO     0x08
#define WD_DEV_UART1_CNTL_CTSAUTO_S   3
#define WD_DEV_UART1_CNTL_AUTORTSC    0x04
#define WD_DEV_UART1_CNTL_AUTORTSC_S  2
#define WD_DEV_UART1_CNTL_TRANSE      0x02
#define WD_DEV_UART1_CNTL_TRANSE_S    1
#define WD_DEV_UART1_CNTL_RCVE        0x01
#define WD_DEV_UART1_CNTL_RCVE_S      0
#define WD_DEV_UART1_CNTL_MSK         0xFF

#define WD_DEV_UART1_STAT             (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x64)))
#define WD_DEV_UART1_STAT_TFIFOLEN    0x0F0000000
#define WD_DEV_UART1_STAT_TFIFOLEN_S  24
#define WD_DEV_UART1_STAT_RFIFOLEN    0x000F0000
#define WD_DEV_UART1_STAT_RFIFOLEN_S  16
#define WD_DEV_UART1_STAT_TRANSDONE   0x00000200
#define WD_DEV_UART1_STAT_TRANSDONE_S 9
#define WD_DEV_UART1_STAT_TFIFOEMP    0x00000100
#define WD_DEV_UART1_STAT_TFIFOEMP_S  8
#define WD_DEV_UART1_STAT_CTS         0x00000080
#define WD_DEV_UART1_STAT_CTS_S       7
#define WD_DEV_UART1_STAT_RTS         0x00000040
#define WD_DEV_UART1_STAT_RTS_S       6
#define WD_DEV_UART1_STAT_TFIFOFULL   0x00000020
#define WD_DEV_UART1_STAT_TFIFOFULL_S 5
#define WD_DEV_UART1_STAT_RCVOVER     0x00000010
#define WD_DEV_UART1_STAT_RCVOVER_S   4
#define WD_DEV_UART1_STAT_TRANSIDLE   0x00000008
#define WD_DEV_UART1_STAT_TRANSIDLE_S 3
#define WD_DEV_UART1_STAT_RCVIDLE     0x00000004
#define WD_DEV_UART1_STAT_RCVIDLE_S   2
#define WD_DEV_UART1_STAT_SPCAV       0x00000002
#define WD_DEV_UART1_STAT_SPCAV_S     1
#define WD_DEV_UART1_STAT_SYMAV       0x00000001
#define WD_DEV_UART1_STAT_SYMAV_S     0
#define WD_DEV_UART1_STAT_MSK         0xF0F03FF

#define WD_DEV_UART1_BAUD             (*((volatile uint32_t *) (WD_DEV_GEN_AUX_BASE + 0x68)))
#define WD_DEV_UART1_BAUD_MSK         0x0000FFFF

/**
 * @brief      Init the UART1 internally
 * 
 * Sets GPIO and cleans. <br>
 * Sets baud to 115200 <br>
 * Enables transmission <br>
 * Defaults to 7 bit <br>
 * 
 * @return False if baud set fail
 */
bool wd_dev_uart1_init();

/**
 * @brief      Sets the GPIO pins to be ready to transmit
 * 
 * Used for real life usage but this can be instead not ran for QEMU debugging <br>
 * <b>CALL THIS BEFORE wd_dev_uart1_init()</br>
 */
void wd_dev_uart1_init_gpio();

/**
 * @brief      Turns on/off the UART1
 * 
 * <b>UART1 MUST BE ANBLED BEFORE ANY OTHER FUNCTIONS ARE USED</b> <br>
 * Also no checks are made if it is enabled
 * 
 * @param[in]  enabled  True to turn on false to turn off
 */
void wd_dev_uart1_set_enabled(bool enabled);
#define wd_dev_uart1_enable() wd_dev_uart1_set_enabled(true)
#define wd_dev_uart1_disable() wd_dev_uart1_set_enabled(false)

/**
 * @brief      Sets the baud rate of the UARt1
 * 
 * @param[in]  baud  The baud rate
 *
 * @return     False if calculated buad value is unable to be fit into 16 bits (too big) or mailbox error
 */
bool wd_dev_uart1_setbaud(unsigned baud);

/**
 * @brief      Write a single character to the FIFO
 * 
 * Aborts if takes over 500ms
 * 
 * @param[in]  data  Character
 */
void wd_dev_uart1_write_char(char data);

/**
 * @brief      Blocking write of data to UART1
 *
 * @param[in]  data    The data
 * @param[in]  length  The length of the data
 */
void wd_dev_uart1_write_data(uint8_t * data, size_t length);

/**
 * @brief      Turns on/off recieve functionality
 * 
 * @param[in]  recieve True to turn on and false to turn off
 */
void wd_dev_uart1_set_reciever(bool recieve);
#define wd_dev_uart1_enable_reciever() wd_dev_uart1_set_reciever(true)
#define wd_dev_uart1_disable_reciever() wd_dev_uart1_set_reciever(false)

/**
 * @brief      Turn on/off transmit functionality
 * 
 * @param[in]  transmit True to enable false to disable
 */
void wd_dev_uart1_set_transmitter(bool transmit);
#define wd_dev_uart1_enable_transmitter() wd_dev_uart1_set_transmitter(true)
#define wd_dev_uart1_disable_transmitter() wd_dev_uart1_set_transmitter(false)

/**
 * @brief      Activates 7 or 8 bit transmission
 * 
 * @param[in]  sevenbit True for 7 bit transmission and false for 8
 */
void wd_dev_uart1_set_bit(bool sevenbit);
#define wd_dev_uart1_enable_sevenbit() wd_dev_uart1_set_bit(true)
#define wd_dev_uart1_enable_eightbit() wd_dev_uart1_set_bit(false)

/**
 * @}
 * @}
 * @}
 */

/**
 * @addtogroup STDIO
 * @{
 */
#define wd_dev_uart1_printf(format, ...) wd_fprintf(&wd_dev_uart1_write_char, format, ##__VA_ARGS__)
/** @} */