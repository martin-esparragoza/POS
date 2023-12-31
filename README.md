# POS
Raspberry Pi soft real-time operating system. For cortex processors only.

# Soft?
* Critical periods are allowed
* There is NO clock. Processes pass priority when done
* No memory protection

# Supported RPIs
Anything with a cortex
- Testing done on a PI3B

# Building
When calling make define PIV to be equal to one of the follwing versions:  
* PI2
* PI2R (PI 2.12)
* PI3B
* PI3BP (PI 3 B+)
* PI4B
These can be defined to anything it doesn't matter.  
BIG_ENDIAN can also be optionally defined (value does not matter)  
To get docs run ```doxygen Doxyfile```

# Features
POS is a minimal operating system that is meant to satisfy the needs to hobbyists. It is not truly real time however operations should be very much so prioritized. It is designed to be fast.

# Driver Standards
* Registers are to be #defined as the VALUE of a volatile pointer
* Bufferes + others are meant to be structures

# To Refactor
* GPIO
* Just look over UART1 for shenanigans
* STDIO