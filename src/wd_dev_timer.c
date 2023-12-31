#include "wd_dev_timer.h"
#include <stdint.h>

uint64_t wd_dev_timer_currenttimeus() {
    uint64_t highbits = WD_DEV_TIMER_CHI;
    highbits <<= 32;
    return highbits | WD_DEV_TIMER_CLO;
}

void wd_dev_timer_waitus(uint64_t us) {
    uint64_t start = wd_dev_timer_currenttimeus();
    while (wd_dev_timer_currenttimeus() - start < us) {;}
}

inline void wd_dev_timer_waitms(uint64_t ms) {
    wd_dev_timer_waitus(ms * 1000);
}