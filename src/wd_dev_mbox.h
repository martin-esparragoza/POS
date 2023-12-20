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
 * Supports 1 mbox
 */

#pragma once
#include <stdint.h>

#define POS_WD_DEV_MBOX_BASE   0xB880
#define POS_WD_DEV_MBOX_RW     (*((volatile uint32_t *) (POS_WD_DEV_MBOX_BASE + 0x00)))
#define POS_WD_DEV_MBOX_PEEK   (*((volatile uint32_t *) (POS_WD_DEV_MBOX_BASE + 0x10)))
#define POS_WD_DEV_MBOX_SENDER (*((volatile uint32_t *) (POS_WD_DEV_MBOX_BASE + 0x14)))
#define POS_WD_DEV_MBOX_STATUS (*((volatile uint32_t *) (POS_WD_DEV_MBOX_BASE + 0x18)))
#define POS_WD_DEV_MBOX_CONFIG (*((volatile uint32_t *) (POS_WD_DEV_MBOX_BASE + 0x3C)))

enum pos_wd_dev_mbox_channel {
    POS_WD_DEV_MBOX_CHANNEL_POWER =            0,
    POS_WD_DEV_MBOX_CHANNEL_FB =               1,
    POS_WD_DEV_MBOX_CHANNEL_VUART =            2,
    POS_WD_DEV_MBOX_CHANNEL_VCHIQ =            3,
    POS_WD_DEV_MBOX_CHANNEL_LED =              4,
    POS_WD_DEV_MBOX_CHANNEL_BUTTON =           5,
    POS_WD_DEV_MBOX_CHANNEL_TOUCH_SCREEN =     6,
    POS_WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC = 8,
    POS_WD_DEV_MBOX_CHANNEL_PROPERTY_VCTOARM = 9,
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
uint32_t pos_wd_dev_mbox_read(enum pos_wd_dev_mbox_channel channel);

/**
 * @brief      Write to mbox channel
 *
 * @param[in]  channel  Channel
 * @param[in]  data     Data to write
 */
void pos_wd_dev_mbox_write(enum pos_wd_dev_mbox_channel channel, uint32_t data);

/**
 * @}
 * @}
 * @}
 */