#include "wd_dev_timer.h"
#include <stdint.h>

uint64_t wd_dev_timer_currenttimeus() {
    uint64_t highbits = WD_DEV_TIMER_CHI;
    highbits <<= 32;
    return highbits | WD_DEV_TIMER_CLO;
}