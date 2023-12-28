/**
 * @file
 * 
 * @addtogroup WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 * 
 * @defgroup   MBOX
 * Mailbox
 * @{
 *
 * @brief      Mailbox drivers for wardpdrive
 * 
 * Supports the first mailbox
 */

#pragma once
#include <stdint.h>

#define WD_DEV_MBOX_BASE   0x3F00B880
#define WD_DEV_MBOX_READ   (*((volatile uint32_t *) (WD_DEV_MBOX_BASE + 0x00)))
#define WD_DEV_MBOX_STATUS (*((volatile uint32_t *) (WD_DEV_MBOX_BASE + 0x18)))
#define WD_DEV_MBOX_WRITE  (*((volatile uint32_t *) (WD_DEV_MBOX_BASE + 0x20)))

enum wd_dev_mbox_channel {
    WD_DEV_MBOX_CHANNEL_POWER =            0,
    WD_DEV_MBOX_CHANNEL_FB =               1,
    WD_DEV_MBOX_CHANNEL_VUART =            2,
    WD_DEV_MBOX_CHANNEL_VCHIQ =            3,
    WD_DEV_MBOX_CHANNEL_LED =              4,
    WD_DEV_MBOX_CHANNEL_BUTTON =           5,
    WD_DEV_MBOX_CHANNEL_TOUCH_SCREEN =     6,
    WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC = 8,
    WD_DEV_MBOX_CHANNEL_PROPERTY_VCTOARM = 9,
};

/**
 * @brief      Read from mbox channel
 *
 * @param[in]  channel  Channel
 *
 * @return     Read value
 * 
 * Discards messages not meant for it
 */
uint32_t wd_dev_mbox_read(enum wd_dev_mbox_channel channel);

/**
 * @brief      Write to mbox channel
 *
 * @param[in]  channel  Channel
 * @param[in]  data     Data to write
 */
void wd_dev_mbox_write(enum wd_dev_mbox_channel channel, uint32_t data);

/**
 * @}
 * @}
 * @}
 */