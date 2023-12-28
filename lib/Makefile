SRCS += $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
DEPFILES = $(patsubst %.c,%.d,$(wildcard *.c))

%.d: %.c
	$(CC) -MM $< -MF $@
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CLINK)

$(STD): $(OBJS)
	$(AR) cr $@ $^

.PHONY: all clean

all: $(DEPFILES) $(STD)

clean:
	rm -rf *.o
	rm -rf *.d
	rm -rf *.a

ifneq ($(MAKECMDGOALS),clean)
include ${DEPFILES}
endif