#include "wd_mem.h"
#include <stdint.h>

void * pos_wd_memcpy(void * src, void * dest, unsigned length) {
    uint8_t * d = dest;
    while (length--)
        *(d++) = *((uint8_t *) src++);
    
    return dest;
}

volatile void * pos_wd_memcpy_vd(void * src, volatile void * dest, unsigned length) {
    volatile uint8_t * d = dest;
    while (length--)
        *(d++) = *((uint8_t* ) src++);

    return dest;
}

void * pos_wd_memcpy_vs(volatile void * src, void * dest, unsigned length) {
    uint8_t * d = dest;
    while (length--)
        *(d++) = *((volatile uint8_t *) src++);
    
    return dest;
}

volatile void * pos_wd_memcpy_vds(volatile void * src, volatile void * dest, unsigned length) {
    volatile uint8_t * d = dest;
    while (length--)
        *(d++) = *((volatile uint8_t *) src++);
    
    return dest;
}