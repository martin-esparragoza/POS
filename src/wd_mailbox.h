/**
 * @file
 * 
 * @addtogroup WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 * 
 * @defgroup   MAILBOX
 * @{
 *
 * @brief      Mailbox drivers for wardpdrive
 */

#pragma once
#include <stdint.h>

#define POS_WD_DEV_MAILBOX_BASE   0xB880
#define POS_WD_DEV_MAILBOX_RW     ((volatile uint32_t *) (POS_WD_DEV_MAILBOX_BASE + 0x00))
#define POS_WD_DEV_MAILBOX_PEEK   ((volatile uint32_t *) (POS_WD_DEV_MAILBOX_BASE + 0x10))
#define POS_WD_DEV_MAILBOX_SENDER ((volatile uint32_t *) (POS_WD_DEV_MAILBOX_BASE + 0x14))
#define POS_WD_DEV_MAILBOX_STATUS ((volatile uint32_t *) (POS_WD_DEV_MAILBOX_BASE + 0x18))
#define POS_WD_DEV_MAILBOX_CONFIG ((volatile uint32_t *) (POS_WD_DEV_MAILBOX_BASE + 0x3C))

enum pos_wd_dev_mailbox_channel {
    POS_WD_DEV_MAILBOX_CHANNEL_POWER =            0,
    POS_WD_DEV_MAILBOX_CHANNEL_FB =               1,
    POS_WD_DEV_MAILBOX_CHANNEL_VUART =            2,
    POS_WD_DEV_MAILBOX_CHANNEL_VCHIQ =            3,
    POS_WD_DEV_MAILBOX_CHANNEL_LED =              4,
    POS_WD_DEV_MAILBOX_CHANNEL_BUTTON =           5,
    POS_WD_DEV_MAILBOX_CHANNEL_TOUCH_SCREEN =     6,
    POS_WD_DEV_MAILBOX_CHANNEL_PROPERTY_ARMTOVC = 8,
    POS_WD_DEV_MAILBOX_CHANNEL_PROPERTY_VCTOARM = 9,
};

enum pos_wd_dev_mailbox {
    POS_WD_DEV_MAILBOX_0 = 0x00,
    POS_WD_DEV_MAILBOX_1 = 0x20
};

#define POS_WD_DEV_MAILBOX_EMPTY 0x40000000 /// Read available
#define POS_WD_DEV_MAILBOX_FULL  0x80000000 /// Write available

/**
 * @brief      Read from mailbox channel
 *
 * @param[in]  channel  Channel
 *
 * @return     Read value
 * 
 * Discards messages not meant for it
 */
uint32_t pos_wd_dev_mailbox_read(enum pos_wd_dev_mailbox mbox, enum pos_wd_dev_mailbox_channel channel);

/**
 * @brief      Write to mailbox channel
 *
 * @param[in]  channel  Channel
 * @param[in]  data     Data to write
 */
void pos_wd_dev_mailbox_write(enum pos_wd_dev_mailbox mbox, enum pos_wd_dev_mailbox_channel channel, uint32_t data);

/**
 * @}
 * @}
 * @}
 */