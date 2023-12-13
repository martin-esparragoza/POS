#include "wd_stdio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

static void print_integer(void (* const write_char)(char), int val);
static inline void print_integer(void (* const write_char)(char), int val) {
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
            }
            continue;
        }

        (*write_char)(format[i]);
    }

    va_end(args);
}