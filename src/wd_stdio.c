#include "wd_stdio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

// There is a bug. I don't know what causes it.
static void print_integer(void (* const write_char)(char), intmax_t val);
static inline void print_integer(void (* const write_char)(char), intmax_t val) {
    uintmax_t divisor;
#if BITS == 32
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
    unsigned char offset = 0;
#if BITS == 32
    offset = __builtin_ffs(val);
#else
    offset = __builtin_ffsll(val);
#endif

    if (((unsigned int) val) != 0)
        offset--;

    mask <<= offset;

    while (mask != 0) {
        (*write_char)('0' + ((val & mask) > 0));
        mask >>= 1;
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
                    print_integer(write_char, va_arg(args, int));
                    break;
                case 'b':
                    print_bin(write_char, va_arg(args, int));
            }
            continue;
        }

        (*write_char)(format[i]);
    }

    va_end(args);
}