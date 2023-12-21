#include "wd_dev_mbox.h"
#include <stdint.h>

uint32_t pos_wd_dev_mbox_read(enum pos_wd_dev_mbox_channel channel) {
    while (1) {
        while ((POS_WD_DEV_MBOX_STATUS & 0x40000000) != 0) {;}

        uint32_t data = POS_WD_DEV_MBOX_READ;
        unsigned char read_channel = data & 0x0F;

        if (read_channel == channel)
            return data >> 4;
    }
}

void pos_wd_dev_mbox_write(enum pos_wd_dev_mbox_channel channel, uint32_t data) {
    while ((POS_WD_DEV_MBOX_STATUS & 0x80000000) != 0) {;}
    POS_WD_DEV_MBOX_WRITE = (data << 4) | channel;
}