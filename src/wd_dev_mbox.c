#include "wd_dev_mbox.h"
#include <stdint.h>

uint32_t wd_dev_mbox_read(enum wd_dev_mbox_channel channel) {
    while (1) {
        while ((WD_DEV_MBOX_STATUS & 0x40000000) != 0) {;}

        uint32_t data = WD_DEV_MBOX_READ;
        unsigned char read_channel = data & 0x0F;

        if (read_channel == channel)
            return data >> 4;
    }
}

void wd_dev_mbox_write(enum wd_dev_mbox_channel channel, uint32_t data) {
    while ((WD_DEV_MBOX_STATUS & 0x80000000) != 0) {;}
    WD_DEV_MBOX_WRITE = (data << 4) | channel;
}