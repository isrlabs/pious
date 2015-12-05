# Set up cross-compilation toolchain
TOOLCHAIN	 = arm-none-eabi
CC		 = $(TOOLCHAIN)-gcc
AS		 = $(TOOLCHAIN)-as
LD		 = $(TOOLCHAIN)-ld
OBJCOPY		 = $(TOOLCHAIN)-objcopy
OBJDUMP		 = $(TOOLCHAIN)-objdump
SIZE		 = $(TOOLCHAIN)-size

# Model should be 1 for the original Model A / Model B, and 2 for
# the A+/B+.
MODEL		?= 2

# Targets
BUILDDIR	 = build
OBJDIR		 = objs
INCLUDES	 = include
SRCDIR		 = src
TARGET		 = kernel.img
LINKER		 = pious.ld
AOUT		 = $(BUILDDIR)/kernel.elf

START		= $(OBJDIR)/start.o
KOBJS		= $(patsubst $(SRCDIR)/kern/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/kern/*.c))
KOBJS		:= $(filter-out $(START),$(KOBJS))
UOBJS		= $(patsubst $(SRCDIR)/shell/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/shell/*.c))
SYSOBJS		= $(patsubst $(SRCDIR)/sys/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/sys/*.c))
OBJS		= $(KOBJS) $(UOBJS) $(SYSOBJS)

MAP		 = $(BUILDDIR)/kernel.map
LIST		 = $(BUILDDIR)/kernel.list
START		 = $(OBJDIR)/start.o

# Build options
MCPU		 = -mcpu=arm1176jzf-s
CFLAGS		+= -O0 -mfpu=vfp -mfloat-abi=soft -march=armv6zk
CFLAGS		+= -mtune=arm1176jzf-s -I$(INCLUDES)
CFLAGS		+= -DMODEL=$(MODEL)


.PHONY: all
all: $(TARGET) $(LIST)

info:
	@echo "This Makefile is still in progress."
	@echo "Objects: $(OBJS)"
	@echo "Source directory: $(SRCDIR)"
	@echo "Sources: $(wildcard $(SRCDIR)/*.c)"
	@echo "a.out: $(AOUT)"

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(AOUT)
	$(OBJCOPY) $(AOUT) -O binary $@
	$(SIZE) $(AOUT)

$(AOUT): $(OBJS) $(LINKER) $(START)
	$(LD) -Map $(MAP) -o $@ -T $(LINKER) $(OBJS) $(START)

$(LIST): $(AOUT)
	$(OBJDUMP) -d $(AOUT) > $@

$(START): $(SRCDIR)/start.s
	$(CC) $(MCPU) -fpic -ffreestanding -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/shell/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/sys/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/kern/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(OBJDIR)/*.d
