#include "wd_dev_mbox.h"
#include "wd_dev_timer.h"
#include <stdint.h>

int32_t wd_dev_mbox_read(enum wd_dev_mbox_channel channel, uint64_t ms) {
    while (1) {
        WD_DEV_TIMER_WAITUNTILCONDITION((WD_DEV_MBOX_STATUS & 0x40000000) == 0, {return -1;}, ms);

        uint32_t data = WD_DEV_MBOX_READ;
        unsigned char read_channel = data & 0x0F;

        if (read_channel == channel) {
            return data >> 4;
        }
    }
}

bool wd_dev_mbox_write(enum wd_dev_mbox_channel channel, uint32_t data, uint64_t ms) {
    WD_DEV_TIMER_WAITUNTILCONDITION((WD_DEV_MBOX_STATUS & 0x80000000) == 0, {return false;}, ms);
    WD_DEV_MBOX_WRITE = (data << 4) | channel;
    return true;
}