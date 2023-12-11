# Define 64BIT in command line arguments

CFLAGS = -fpic -ffreestanding -std=gnu99 -Wall -O0 -Wextra -mabi=aapcs
CLINK =
ASMFLAGS = -Wall -Wextra -fpic -ffreestanding -O0
ASMLINK =
LINKFLAGS = -ffreestanding -O1 -nostdlib
LINKLINK = -lgcc

# DEFAULT: pi2
PIV = PI2

ifeq ($(PIV),PI2)
	CC = arm-none-eabi-gcc
	ASM = arm-none-eabi-gcc
	LINK = arm-none-eabi-gcc
	OBJCOPY = arm-none-eabi-objcopy
	CFLAGS += -mcpu=cortex-a7
	ASMFLAGS += -mcpu=cortex-a7
else ifeq ($(PIV),$(filter $(PIV), PI2R PI3B PI3BP))
	CFLAGS += -mcpu=cortex-a53
	ASMFLAGS += -mcpu=cortex-a53
else ifdef ($(PIV),PI4B)
	CFLAGS += -mcpu=cortex-a72
	ASMFLAGS += -mcpu=cortex-a72
else
$(error "BAD PI")
endif

ifeq ($(PIV),$(filter $(PIV),PI3 PI3B PI3BP PI4B))
	CC = aarch64-elf-gcc
	ASM = aarch64-elf-as
	LINK = aarch64-elf-gcc 
	OBJCOPY = aarch64-elf-objcopy
endif

ifdef PI2
else
	CFLAGS += -mcpu=cortex-a7 -marm
	ASMFLAGS += -mcpu=cortex-a7
endif

ifdef BIG_ENDIAN
	CFLAGS += -mbig-endian
endif

CFLAGS += -D PIV=$(PIV)

export

MAKEDIRS = lib/ src/

.PHONY: all clean $(MAKEDIRS)
	
all: $(MAKEDIRS)
	
clean: $(MAKEDIRS)

$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)