#include "wd_stdio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

// There is a bug. I don't know what causes it.
static void print_integer(void (* const write_char)(char), intmax_t val);
static inline void print_integer(void (* const write_char)(char), intmax_t val) {
    uintmax_t divisor;
#if BIT == 32
    divisor = 1000000000;
#else
    divisor = 1000000000000000000;
#endif
    bool numprinted = false;

    if (val < 0) {
        (*write_char)('-');
        val *= -1;
    }

    while (divisor != 0) {
        unsigned char digit = val / divisor;
        if (numprinted || divisor == 1 || digit != 0) {
            (*write_char)('0' + digit);
            numprinted = true;
        }
        val %= divisor;
        divisor /= 10;
    }
}

static void print_bin(void (* const write_char)(char), intmax_t val);
static inline void print_bin(void (* const write_char)(char), intmax_t val) {
    uintmax_t mask = 1;
    signed char offset = 0;
#if BIT == 32
    offset = __builtin_ctz(val);
#else
    offset = __builtin_ctzll(val);
#endif

    if (val == 0) {
        offset = 0;
    }

    offset = 63;

    mask <<= offset;

    while (mask != 0) {
        (*write_char)('0' + ((val & mask) > 0));
        mask >>= 1;
    }
}

static char hexmap[] = "0123456789ABCDEF";

static void print_hex(void (*const write_char)(char), uintmax_t val);
static inline void print_hex(void (*const write_char)(char), uintmax_t val) {
    uintmax_t mask = 0x0F;
    signed char offset = 0;
#if BIT == 32
    offset = -__builtin_clz(val);
#else
    offset = -__builtin_clzll(val);
#endif
    offset += BIT;

    // Allign to 4 bit boundary
    offset = (offset + 3) & ~3;

    if (offset < 0 || val == 0) {
        offset = 0;
    } else {
        // Subrtact 4 because 1 is attributed to __builtin_clz and the other 3 are attributed to hex being 4 bit aligned
        offset -= 4;
    }
    mask <<= offset;

    while (mask != 0) {
        (*write_char)(hexmap[(val & mask) >> offset]);
        offset -= 4;
        mask >>= 4;
    }
}

void pos_wd_fprintf(void (* const write_char)(char), const char * format, ...) {
    va_list args;
    va_start(args, format);

    for (unsigned i = 0; format[i] != '\0'; i++) {
        // Expecting format
        if (format[i] == '%') {
            switch (format[(i++) + 1]) {
                case 'd':
                    print_integer(write_char, va_arg(args, uintmax_t));
                    break;
                case 'b':
                    print_bin(write_char, va_arg(args, uintmax_t));
                    break;
                case 'x':
                    print_hex(write_char, va_arg(args, uintmax_t));
            }
            continue;
        }

        (*write_char)(format[i]);
    }

    va_end(args);
}