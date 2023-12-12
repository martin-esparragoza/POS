# Define 64BIT in command line arguments

CFLAGS = -fpic -ffreestanding -std=gnu99 -Wall -O0 -Wextra -std=c99
CLINK =
ASMFLAGS =
ASMLINK =
LINKFLAGS = -ffreestanding -O1 -nostdlib
LINKLINK = -lgcc
BIT = 32

# DEFAULT: pi3ap
PIV = PI3AP

ifeq ($(PIV),PI2)
	CC = arm-none-eabi-gcc
	ASM = arm-none-eabi-gcc
	LINK = arm-none-eabi-gcc
	OBJCOPY = arm-none-eabi-objcopy
	CFLAGS += -mcpu=cortex-a7 -mabi=aapcs
	ASMFLAGS += -mcpu=cortex-a7
	ASMFLAGS += -Wall -Wextra -fpic -O0 -ffreestanding
else ifeq ($(PIV),$(filter $(PIV), PI2R PI3AP PI3B))
	CFLAGS += -mcpu=cortex-a53
	ASMFLAGS += -mcpu=cortex-a53
else ifdef ($(PIV),PI4B)
	CFLAGS += -mcpu=cortex-a72
	ASMFLAGS += -mcpu=cortex-a72
else
$(error "BAD PI")
endif

ifeq ($(PIV),$(filter $(PIV),PI3 PI3AP PI3B PI4B))
	CC = aarch64-none-elf-gcc
	ASM = aarch64-none-elf-as
	LINK = aarch64-none-elf-gcc 
	OBJCOPY = aarch64-none-elf-objcopy
	CFLAGS += -mabi=lp64
	BIT = 64
endif

ifdef BIG_ENDIAN
	CFLAGS += -mbig-endian
endif

CFLAGS += -D PIV=$(PIV) -D BIT=$(BIT)

export

MAKEDIRS = lib/ src/

.PHONY: all clean $(MAKEDIRS)
	
all: $(MAKEDIRS)
	
clean: $(MAKEDIRS)

$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)