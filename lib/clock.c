#include "../include/clock.h"

// Stolen
inline void delay_cycles(unsigned long count) {
	__asm__ volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}