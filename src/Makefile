# TODO: deps

.PHONY: all clean

SRCS =
	
ifdef 64BIT
else
	SRCS += boot32.S
endif

SRCS += $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
DEPFILES = $(patsubst %.c,%.d,$(wildcard *.c))

all: $(DEPFILES) $(OBJS) kernel.img

clean:
	rm -rf *.o
	rm -rf *.img
	rm -rf *.elf
	rm -rf *.d
	
%.o: %.S
	$(ASM) $(ASMFLAGS) -c $< -o $@ $(ASMLINK)
	
%.d: %.c
	$(CC) -MM $< -MF $@
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CLINK)
	
# TODO: make this not garbage
%.img: $(OBJS)
	$(LINK) -T linker.ld -o intermediate.elf $(LINKFLAGS) $(OBJS) $(LINKLINK)
	$(OBJCOPY) intermediate.elf -O binary $@
	
ifneq ($(MAKECMDGOALS),clean)
include ${DEPFILES}
endif