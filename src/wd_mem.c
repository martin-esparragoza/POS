#include "wd_mem.h"
#include <stdint.h>

void * pos_wd_memcpy(void * src, void * dest, unsigned len) {
    uint8_t * d = dest;
    while (len--)
        *(d++) = *((uint8_t *) src++);
    
    return dest;
}

volatile void * pos_wd_memcpy_vd(void * src, volatile void * dest, unsigned len) {
    volatile uint8_t * d = dest;
    while (len--)
        *(d++) = *((uint8_t* ) src++);

    return dest;
}

void * pos_wd_memcpy_vs(volatile void * src, void * dest, unsigned len) {
    uint8_t * d = dest;
    while (len--)
        *(d++) = *((volatile uint8_t *) src++);
    
    return dest;
}

volatile void * pos_wd_memcpy_vds(volatile void * src, volatile void * dest, unsigned len) {
    volatile uint8_t * d = dest;
    while (len--)
        *(d++) = *((volatile uint8_t *) src++);
    
    return dest;
}

void * pos_wd_memset(void * src, unsigned char val, unsigned len) {
    uint8_t * s = src;
    while (len--)
        *(s++) = val;

    return src;
}