# POS
Raspberry PI operating system. For cortex processors only.

# Why?
Fast. Low level control. C libraries to control hardware. Emulated flash memory run on boot. Drivers for many. 

# Supported RPIs
Anything with a cortex
- TODO: More than RPI 2

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

# STDLIB
Standard library is in /include and /lib. A more primitive form of some of the standard library is used in the warp drive, although should not be used outside of it.