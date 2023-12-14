# POS
Raspberry Pi FAKE real-time operating system. For cortex processors only.

# FAKE?
POS is a FAKE real-time operating system. It does not stick to the traditional definition of a real time operating system as it does not GUARANTEE that something is handled instantly. Hardware access will not be ripped out of a driver's hands instantly and instead it will be given VERY minimal time to panic and store state. This does not change the fact that drivers should be designed to panic. 

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