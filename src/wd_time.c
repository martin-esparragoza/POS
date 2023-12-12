#include "wd_time.h"
#include <stdint.h>

// Stolen
void pos_wd_delay(uint32_t count);
inline void pos_wd_delay(uint32_t count) {
	__asm__ volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}