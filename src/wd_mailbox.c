#include "wd_mailbox.h"
#include <stdint.h>

static inline uint32_t read_register(enum pos_wd_dev_mailbox mbox, volatile uint32_t * reg);
static inline uint32_t read_register(enum pos_wd_dev_mailbox mbox, volatile uint32_t * reg) {
    return *(reg + mbox);
}

static inline void write_register(enum pos_wd_dev_mailbox mbox, volatile uint32_t * reg, uint32_t data);
static inline void write_register(enum pos_wd_dev_mailbox mbox, volatile uint32_t * reg, uint32_t data) {
    *(reg + mbox) = data;
}

uint32_t pos_wd_dev_mailbox_read(enum pos_wd_dev_mailbox mbox, enum pos_wd_dev_mailbox_channel channel) {
    while (1) {
        while ((read_register(mbox, POS_WD_DEV_MAILBOX_STATUS) & POS_WD_DEV_MAILBOX_EMPTY) != 0) {;}

        uint32_t data = read_register(mbox, POS_WD_DEV_MAILBOX_RW);
        unsigned char read_channel = data & 0x0F;
        data >>= 4;

        if (read_channel == channel)
            return data;
    }
}

void pos_wd_dev_mailbox_write(enum pos_wd_dev_mailbox mbox, enum pos_wd_dev_mailbox_channel channel, uint32_t data) {
    while ((read_register(mbox, POS_WD_DEV_MAILBOX_STATUS) & POS_WD_DEV_MAILBOX_FULL) != 0) {;}
    write_register(mbox, POS_WD_DEV_MAILBOX_RW, (data << 4) | channel);
}