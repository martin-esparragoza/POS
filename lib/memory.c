#include "../include/memory.h"
#include <stdint.h>
#include <stddef.h>

void * memcpy(void * dest, void * src, size_t len) {
    uint8_t * d = dest;
    while (len--)
        *(d++) = *((uint8_t *) src++);
    
    return dest;
}


volatile void * memcpy_vd(volatile void * dest, void * src, size_t len) {
    volatile uint8_t * d = dest;
    while (len--)
        *(d++) = *((uint8_t* ) src++);

    return dest;
}

void * memcpy_vs(void * dest, volatile void * src, size_t len) {
    uint8_t * d = dest;
    while (len--)
        *(d++) = *((volatile uint8_t *) src++);
    
    return dest;
}

volatile void * memcpy_vds(volatile void * dest, volatile void * src, size_t len) {
    volatile uint8_t * d = dest;
    while (len--)
        *(d++) = *((volatile uint8_t *) src++);
    
    return dest;
}

void * memset(void * dest, unsigned char val, size_t len) {
    uint8_t * d = dest;
    while (len--)
        *(d++) = val;

    return dest;
}