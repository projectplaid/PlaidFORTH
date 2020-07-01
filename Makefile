SSRCS = start.S forth.S
SOBJS = $(SSRCS:.S=.o)

CSRCS = mbox.c uart.c support.c
COBJS = $(CSRCS:.c=.o)

XCC=aarch64-none-elf-gcc
XCFLAGS=-O0 -g -ffreestanding -nostartfiles
XLDFLAGS=-Wl,-Tlinker.ld -nostdlib -nostartfiles
XLDADD=

all: plaid.elf

%.o: %.c
	$(XCC) $(XCFLAGS) -c $< -o $@

%.o: %.S forth.f
	$(XCC) $(XCFLAGS) -c $< -o $@

plaid.elf: $(SOBJS) $(COBJS)
	$(XCC) $(XCFLAGS) $(XLDFLAGS) -o plaid.elf $(SOBJS) $(COBJS) $(XLDADD)

clean:
	rm -f *.o *.elf

.PHONY: all clean